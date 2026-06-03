# Import Flask framework
from flask import Flask

# Import request object for receiving data
from flask import request

# Import jsonify for sending JSON responses
from flask import jsonify


# Import requests library for HTTP requests
import requests

# Import os library for environment variables
import os

# Import urllib3 library
# We had issues with SSL certificate
import urllib3

# Disable SSL certificate warnings
urllib3.disable_warnings(
    urllib3.exceptions.InsecureRequestWarning
)


# Import dotenv library
from dotenv import load_dotenv

# Import OAuth2 token function
from services.token_manager import \
    get_valid_token

# Load .env variables into Python
load_dotenv()


# Create Flask application
app = Flask(__name__)

# Read FIWARE broker URL from .env 
# Included separately

FIWARE_BROKER = os.getenv(
    "FIWARE_BROKER"
)

# Read FIWARE service name from .env
FIWARE_SERVICE = os.getenv(
    "FIWARE_SERVICE"
)

# Read FIWARE service path from .env
FIWARE_SERVICEPATH = os.getenv(
    "FIWARE_SERVICEPATH"
)


# =====================
# HOME ROUTE
# =====================

# Flask route for homepage
@app.route('/')

# Function for homepage
def home():

    # Return backend status message
    return "FIWARE Backend Running"


# =====================
# MOTION ROUTE
# =====================

# Flask route for receiving motion data
@app.route('/motion',
           methods=['POST'])

# Function for motion API
def motion():

    try:

        # Read incoming JSON data
        data = request.json

        # Print received JSON
        print("\nReceived:",
              data)

        # Extract motion value
        motion_status = data.get(
            "motion"
        )

        # Get OAuth2 access token
        token = get_valid_token()

        # Create Orion entity URL
        url = (
            f"{FIWARE_BROKER}"
            "/v2/entities/PIR001/attrs"
        )

        # Create HTTP headers
        headers = {

            # Set JSON content type
            "Content-Type":
                "application/json",

            # Add OAuth2 access token
            "X-Auth-Token":
                token,

            # Add FIWARE service
            "fiware-service":
                FIWARE_SERVICE,

            # Add FIWARE service path
            "fiware-servicepath":
                FIWARE_SERVICEPATH
        }

        # Create JSON payload
        payload = {

            # Update motion attribute
            "motion": {

                # Set motion value
                "value":
                    motion_status,

                # Set data type
                "type":
                    "Boolean"
            }
        }

        # Send PATCH request to Orion
        response = requests.patch(
            url,
            json=payload,
            headers=headers,
            verify=False
        )

        # Print Orion status code
        print(
            "Orion Status:",
            response.status_code
        )

        # Print Orion response
        print(
            "Orion Response:",
            response.text
        )

        # Return success response
        return jsonify({
            "message":
                "Motion updated"
        })

    # Catch errors
    except Exception as e:

        # Print error message
        print("ERROR:",
              str(e))

        # Return error response
        return jsonify({
            "error":
                str(e)
        }), 500


# =====================
# ALARM ROUTE
# =====================

# Flask route for reading alarm state
@app.route('/alarm',
           methods=['GET'])

# Function for alarm API
def get_alarm():

    try:

        # Get OAuth2 access token
        token = get_valid_token()

        # Create Orion entity URL
        url = (
            f"{FIWARE_BROKER}"
            "/v2/entities/PIR001"
        )

        # Create HTTP headers
        headers = {

            # Add OAuth2 token
            "X-Auth-Token":
                token,

            # Add FIWARE service
            "fiware-service":
                FIWARE_SERVICE,

            # Add FIWARE service path
            "fiware-servicepath":
                FIWARE_SERVICEPATH
        }

        # Send GET request to Orion
        response = requests.get(
            url,
            headers=headers,
            verify=False
        )

        # Convert JSON response into Python dictionary
        entity = response.json()

        # Extract alarm value
        alarm_value = entity[
            "alarm"
        ]["value"]

        # Return alarm state to ESP32
        return jsonify({
            "alarm":
                alarm_value
        })

    # Catch errors
    except Exception as e:

        # Return error response
        return jsonify({
            "error":
                str(e)
        }), 500


# =====================
# START FLASK SERVER
# =====================

# Check if file runs directly
if __name__ == '__main__':

    # Start Flask backend server
    app.run(

        # Enable debug mode
        debug=True,

        # Allow network access
        host='0.0.0.0',

        # Run server on port 5050
        port=5050
    )
