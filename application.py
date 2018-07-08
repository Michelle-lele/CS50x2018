import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the data for stocks in portfolio
    portfolio = db.execute(
                    "SELECT symbol, sum(shares), avg(price), sum(total) FROM portfolio WHERE id = :id GROUP BY symbol HAVING (sum(shares) > 0) ORDER BY sum(total) DESC", id=session.get("user_id"))

    # Create list of dictionaries for the stocks table
    portfolios = []
    for i in range(len(portfolio)):
        portfolios.append({'symbol': portfolio[i]['symbol'], 'sum_shares': portfolio[i]['sum(shares)'], 'avg_price': usd(portfolio[i]['avg(price)']), 'total': usd(
            portfolio[i]['sum(total)'])})

    # Get the currenct cash value
    cash_list = db.execute("SELECT cash FROM users WHERE id=:id", id=session.get("user_id"))
    cash = usd(cash_list[0]['cash'])

    # Get the total value of user's portfolio
    totals_stocks = db.execute("SELECT sum(total) FROM portfolio WHERE id = :id", id=session.get("user_id"))

    # Handle if user doesn't have stocks in the portfolio
    if totals_stocks[0]['sum(total)'] != None:
        grand_total = usd(float(cash_list[0]['cash']) + float(totals_stocks[0]['sum(total)']))
    else:
        grand_total = usd(float(cash_list[0]['cash']))

    return render_template("index.html", portfolios=portfolios, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Get user input for stock symbol
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure shares were submited
        if not request.form.get("shares"):
            return apology("must provide number of shares to buy", 403)

        # Ensure user provided a whole number of shares (int)
        try :
            int(request.form.get("shares"))
        except ValueError:
            return apology("must provide a whole number of shares", 400)

        # Ensure user provided positive number of shares
        if int(request.form.get("shares")) <= 0:
            return apology("must provide positive number of shares", 400)

        # Enure symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("must provide valid symbol", 400)

        # Get shares price
        stock = lookup(request.form.get("symbol"))
        stock['shares'] = request.form.get("shares")

        # Check if user has enough cash
        quote = stock['price'] * float(stock['shares'])
        # print(quote)
        cash_list = db.execute("SELECT cash FROM users WHERE id=:id", id=session.get("user_id"))
        cash = cash_list[0]['cash']

        if quote > cash:
            return apology("Not enough money in account", 403)

        # "Buy" stock and save purchase data in db
        db.execute("INSERT INTO portfolio (id, symbol, shares, price, total) VALUES (:id, :symbol, :shares, :price, :total)",
                    id=session.get("user_id"), symbol=stock['symbol'], shares=stock['shares'], price=stock['price'], total=quote)
        # Update user cash
        db.execute("UPDATE users SET cash = cash - :quote WHERE id=:id", quote=quote, id=session.get("user_id"))
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the data for stocks in portfolio
    history = db.execute(
        "SELECT symbol, shares, price, transaction_time FROM portfolio WHERE id =:id ORDER BY transaction_time DESC", id=session.get("user_id"))

    # Create list of dictionaries for the history table
    history_table = []
    for i in range(len(history)):
        history_table.append({'symbol': history[i]['symbol'], 'shares': history[i]['shares'],
                     'price': usd(history[i]['price']), 'transacted': history[i]['transaction_time']})

    return render_template("history.html", history_table=history_table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Check if symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("symbol not found", 400)
        else:
            stock = lookup(request.form.get("symbol"))
            return render_template("quoted.html", price=usd(stock['price']), symbol=stock['symbol'])
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure username is not existing
        usernames = db.execute("SELECT username FROM users")
        # print(usernames)
        for i in range(len(usernames)):
            if request.form.get("username") == usernames[i]['username']:
                return apology("username already exists", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure password and confirmation password match
        if request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords doesn't match", 400)

        # Save username and hashed password to db
        rows = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get(
                "username"), hash=generate_password_hash(request.form.get("password"),  method='pbkdf2:sha256', salt_length=8))

        # Redirect user to home page
        return login()

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    portfolio = db.execute("SELECT symbol FROM portfolio WHERE id=:id GROUP BY symbol", id=session.get("user_id"))
    # print(portfolio)
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure shares were submited
        if not request.form.get("shares"):
            return apology("must provide number of shares to sell", 400)

        # Ensure user provided positive number of shares
        if int(request.form.get("shares")) <= 0:
            return apology("must provide positive number of shares", 400)

        # Enure symbol exists
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("must provide valid symbol", 400)

        # Enure symbol exists in user portfolio
        symbol = stock['symbol']
        if isInPortfolio(symbol, portfolio) != True:
            return apology("must provide symbol that you own", 400)

        # Ensure users provides no more shares than he owns
        shares_owned = db.execute("SELECT sum(shares) FROM portfolio WHERE id=:id and symbol=:symbol",
                            id=session.get("user_id"), symbol=symbol)
        if int(request.form.get("shares")) > shares_owned[0]['sum(shares)']:
            return apology("must provide no more shares than you own", 400)

        # "Sell" stocks on current price and remove sold stocks from portfolio
        # print(-int(request.form.get("shares")) + 2)
        curr_price = stock['price'] * float(request.form.get("shares"))
        db.execute("INSERT INTO portfolio (id, symbol, shares, price, total) VALUES (:id, :symbol, :shares, :price, :total)", id=session.get(
                "user_id"), symbol=symbol, shares=-int(request.form.get("shares")), price=stock['price'], total=-curr_price)
        # Update user cash
        db.execute("UPDATE users SET cash = cash + :curr_price WHERE id=:id", curr_price=curr_price, id=session.get("user_id"))
        return redirect("/")
    return render_template("sell.html", portfolio=portfolio)


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        # Ensure old password was submitted
        if not request.form.get("old-password"):
            return apology("must provide old password", 400)

        # Ensure new password was submitted
        if not request.form.get("new-password"):
            return apology("must provide new password", 400)

        # Ensure confirmation password was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure password and confirmation password match
        if request.form.get("confirmation") != request.form.get("new-password"):
            return apology("passwords doesn't match", 400)

        # Ensure that old password matches existing one
        old_hash = db.execute("SELECT hash FROM users WHERE id = :id", id=session.get("user_id"))

        if check_password_hash(old_hash, request.form.get("old-password")):
            return apology("incorrect password", 403)

        # Update user password with new one
        db.execute("UPDATE users SET hash= :hash WHERE id=:id", hash=generate_password_hash(
            request.form.get("new-password"),  method='pbkdf2:sha256', salt_length=8), id=session.get("user_id"))

    return render_template("change_password.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


# checks if symbol is in give portfolio
def isInPortfolio(symbol, portfolio):
    s = symbol.upper()
    for i in range(len(portfolio)):
        if s == portfolio[i]['symbol']:
            return True
    return False

'''
@app.context_processor
@login_required
# Put username greeting for logged in users
def inject_username():
    user = db.execute("SELECT username FROM users WHERE id=:id", id=session.get("user_id"))
    print(user)
    username = user[0]['username']
    return dict(username=username)
'''