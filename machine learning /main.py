
import ccxt

# Initialize Binance API
exchange = ccxt.binance()

# Fetch BTC/USDT price
ticker = exchange.fetch_ticker("BTC/USDT")
print(f"Bitcoin Price: {ticker['last']} USDT")

