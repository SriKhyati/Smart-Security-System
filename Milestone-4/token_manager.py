import requests
import os
import time
import urllib3

urllib3.disable_warnings(
    urllib3.exceptions.InsecureRequestWarning
)

from dotenv import load_dotenv
from pathlib import Path

env_path = Path(__file__).resolve().parent.parent / '.env'

load_dotenv(dotenv_path=env_path)

FIWARE_IDM = os.getenv("FIWARE_IDM")

print("FIWARE_IDM =", FIWARE_IDM)

USERNAME = os.getenv("FIWARE_USERNAME")

PASSWORD = os.getenv("FIWARE_PASSWORD")

CLIENT_ID = os.getenv("FIWARE_CLIENT_ID")

CLIENT_SECRET = os.getenv("FIWARE_CLIENT_SECRET")

access_token = None
token_expiry = 0


def request_new_token():

    global access_token
    global token_expiry

    print("\nRequesting NEW token...")

    url = f"{FIWARE_IDM}/oauth2/token"

    payload = {
    "grant_type": "password",
    "username": USERNAME,
    "password": PASSWORD,
    "client_id": CLIENT_ID,
    "client_secret": CLIENT_SECRET
}

    headers = {
        "Content-Type":
        "application/x-www-form-urlencoded"
    }

    response = requests.post(
        url,
        data=payload,
        headers=headers,
        verify=False
    )
    print("\n========== TOKEN DEBUG ==========")
    print("STATUS CODE:", response.status_code)
    print("RAW RESPONSE:")
    print(response.text)
    print("=================================\n")

    print("Status:",
          response.status_code)

    print("Response:",
          response.text)

    if response.status_code != 200:

        raise Exception(
        f"Token request failed: {response.text}"
        )

    token_data = response.json()

    access_token = token_data["access_token"]

    expires_in = token_data.get(
        "expires_in",
        3600
    )

    token_expiry = (
        time.time() + expires_in
    )

    print("Token saved")

    return access_token


def get_valid_token():

    global access_token
    global token_expiry

    current_time = time.time()

    if access_token and \
       current_time < token_expiry:

        print("\nUsing existing token")

        return access_token

    return request_new_token()