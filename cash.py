from cs50 import get_float

quarters = 25
dimes = 10
nickels = 5
pennies = 1

# prompt user to type change until positive number is entered
while True:
    print("O hai! How much change is owed?")
    change = get_float()
    if change > 0.00:
        break
coins = 0
remaining_change = round(change * 100)
# print(f"{remaining_change}")

# calculates the minimum amount of coins needed for the change


def coins_number(remaining_change):
    global coins
    if remaining_change <= 0:
        return coins

    if remaining_change >= quarters:
        remaining_change -= quarters
        coins += 1
        # print(f"25, {coins}, {remaining_change}")
    elif remaining_change >= dimes:
        remaining_change -= dimes
        coins += 1
        # print(f"10, {coins}, {remaining_change}")
    elif remaining_change >= nickels:
        remaining_change -= nickels
        coins += 1
        # print(f"5, {coins}, {remaining_change}")
    elif remaining_change >= pennies:
        remaining_change -= pennies
        coins += 1
        # print(1, f"{coins}, {remaining_change}")
    coins_number(remaining_change)
    return coins


print(f"{coins_number(remaining_change)}")