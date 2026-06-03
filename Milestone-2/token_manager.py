# Import requests library for HTTP requests
import requests

# Import os library for environment variables
import os

# Import time library for token expiry calculation
import time

# Import urllib3 library
import urllib3

# SSL certificate warnings.
urllib3.disable_warnings(
    urllib3.exceptions.InsecureRequestWarning
)

# Import dotenv library
from dotenv import load_dotenv

# Import Path library for file paths
from pathlib import Path

# Create path to .env file
env_path = Path(__file__).resolve().parent.parent / '.env'

# Load environment variables from .env
load_dotenv(dotenv_path=env_path)

# Read FIWARE IDM URL from .env
FIWARE_IDM = os.getenv("FIWARE_IDM")

# Print IDM URL for debugging
print("FIWARE_IDM =", FIWARE_IDM)

# Read FIWARE username from .env
USERNAME = os.getenv("FIWARE_USERNAME")

# Read FIWARE password from .env
PASSWORD = os.getenv("FIWARE_PASSWORD")

# Read OAuth2 client ID from .env
CLIENT_ID = os.getenv("FIWARE_CLIENT_ID")

# Read OAuth2 client secret from .env
CLIENT_SECRET = os.getenv("FIWARE_CLIENT_SECRET")

# Store access token globally
access_token = None

# Store token expiry time
token_expiry = 0


# =====================
# REQUEST NEW TOKEN
# =====================

# Function for requesting new OAuth2 token
def request_new_token():

    # Access global token variable
    global access_token

    # Access global expiry variable
    global token_expiry

    # Print token request message
    print("\nRequesting NEW token...")

    # Create Keyrock token URL
    url = f"{FIWARE_IDM}/oauth2/token"

    # Create OAuth2 payload
    payload = {

    # OAuth2 password grant type
    "grant_type": "password",

    # FIWARE username
    "username": USERNAME,

    # FIWARE password
    "password": PASSWORD,

    # OAuth2 client ID
    "client_id": CLIENT_ID,

    # OAuth2 client secret
    "client_secret": CLIENT_SECRET
}

    # Create HTTP headers
    headers = {

        # Set form-urlencoded content type
        "Content-Type":
        "application/x-www-form-urlencoded"
    }

    # Send POST request to Keyrock IDM
    response = requests.post(

        # Token endpoint URL
        url,

        # OAuth2 payload
        data=payload,

        # HTTP headers
        headers=headers,

        # Disable SSL verification
        verify=False
    )

    # =====================
    # DEBUG OUTPUT
    # =====================

    # Print debug separator
    print("\n========== TOKEN DEBUG ==========")

    # Print HTTP status code
    print("STATUS CODE:", response.status_code)

    # Print raw server response
    print("RAW RESPONSE:")

    # Display response body
    print(response.text)

    # Print debug separator
    print("=================================\n")

    # Print response status
    print("Status:",
          response.status_code)

    # Print response text
    print("Response:",
          response.text)

    # Check if request failed
    if response.status_code != 200:

        # Raise error if token request fails
        raise Exception(
        f"Token request failed: {response.text}"
        )

    # Convert JSON response into Python dictionary
    token_data = response.json()

    # Extract access token
    access_token = token_data["access_token"]

    # Read token expiry time
    expires_in = token_data.get(
        "expires_in",
        3600
    )

    # Calculate token expiry timestamp
    token_expiry = (
        time.time() + expires_in
    )

    # Print token saved message
    print("Token saved")

    # Return access token
    return access_token


# =====================
# GET VALID TOKEN
# =====================

# Function for checking token validity
def get_valid_token():

    # Access global token variable
    global access_token

    # Access global expiry variable
    global token_expiry

    # Get current system time
    current_time = time.time()

    # Check if token exists and still valid
    if access_token and \
       current_time < token_expiry:

        # Print reuse token message
        print("\nUsing existing token")

        # Return existing token
        return access_token

    # Request new token if expired
    return request_new_token()
