from cs50 import SQL

# print(40.03 * 13)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

'''
cash_list = db.execute("SELECT cash FROM users WHERE id=:id", id=49)
print(cash_list)
print(cash_list[0])
cash_dict= cash_list[0]

cash = cash_dict['cash']

quote = 10009
print((quote > cash))

list = ['a', 'b', 'c', 10000]
# print(list)
# print(list[3])

dict = {'value': 'a', 'second': 'b', 'third': 'c', 'cash': 10000}
# print(dict)
# print(dict['cash'])

id=10
symbol="AAPL"
shares=2
price=1.11

print(db.execute("INSERT INTO portfolio (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id =id, symbol=symbol, shares=shares, price=price))

list = [{'symbol': 'AAPL', 'sum(shares)': 45, 'round(avg(price),2)': 123.78}, {'symbol': 'ORCL', 'sum(shares)': 108, 'round(avg(price),2)': 36.86}]

for i in range(len(list)):
    lists = [{'symbol': list[i]['symbol'], 'sum_shares': list[i]['sum(shares)'], 'avg_price': list[i]['round(avg(price),2)']}]
    print(list[i]['symbol'])
    print(list[i]['sum(shares)'])
    print(list[i]['round(avg(price),2)'])
    list[i].update()
print(lists)


print(db.execute("SELECT sum(total) FROM portfolio WHERE id = 10"))


portfolio = db.execute("SELECT symbol, sum(shares) FROM portfolio WHERE id = 10 GROUP BY symbol")
print(portfolio)
symbol = 'Bbcdd'

def isInPortfolio(symbol, portfolio):
    s = symbol.upper()
    for i in range(len(portfolio)):
        if s == portfolio[i]['symbol']:
            return True

    return False

print(isInPortfolio(symbol, portfolio))

list = {'price': 25.86, 'symbol': 'DDT'}
print(list['price'])
'''

this = 3.0

print(isinstance(this, int))

if isinstance(this, int) == False:
    print("Not")

if isinstance(this, int):
        print("Yaaaas")

