# =====================================================
# SMART SECURITY BACKEND
# Flask + Orion Context Broker
# =====================================================

from flask import Flask
from flask import request
from flask import jsonify

import requests
import os
import urllib3

from dotenv import load_dotenv

from services.token_manager import \
    get_valid_token

# Disable SSL warnings
urllib3.disable_warnings(
    urllib3.exceptions.InsecureRequestWarning
)

# =====================================================
# LOAD ENVIRONMENT VARIABLES
# =====================================================

load_dotenv()

# =====================================================
# FLASK APP
# =====================================================

app = Flask(__name__)

# =====================================================
# FIWARE VARIABLES
# =====================================================

FIWARE_BROKER = os.getenv(
    "FIWARE_BROKER"
)

FIWARE_SERVICE = os.getenv(
    "FIWARE_SERVICE"
)

FIWARE_SERVICEPATH = os.getenv(
    "FIWARE_SERVICEPATH"
)

# =====================================================
# HOME ROUTE
# =====================================================

@app.route('/')

def home():

    return "SMART SECURITY BACKEND RUNNING"

# =====================================================
# SECURITY ROUTE
# Receives sensor data from ESP32
# =====================================================

@app.route(
    '/security',
    methods=['POST']
)

def security_data():

    try:

        # =========================================
        # RECEIVE JSON FROM ESP32
        # =========================================

        data = request.json

        print(
            "\nReceived Security Data:"
        )

        print(data)

        # =========================================
        # EXTRACT VALUES
        # =========================================

        temperature = data.get(
            "temperature"
        )

        humidity = data.get(
            "humidity"
        )

        motion = data.get(
            "motion"
        )

        distance = data.get(
            "distance"
        )

        armed = data.get(
            "armed"
        )

        alarm = data.get(
            "alarm"
        )

        # =========================================
        # GET VALID TOKEN
        # =========================================

        token = get_valid_token()

        # If token failed
        if not token:

            return jsonify({

                "error":
                "OAuth Token Failed"
            }), 500

        # =========================================
        # ORION URL
        # IMPORTANT:
        # Short entity name to avoid
        # Grafana/MySQL issues
        # =========================================

        url = (
            f"{FIWARE_BROKER}"
            "/v2/entities/ss1/attrs"
        )

        # =========================================
        # HEADERS
        # =========================================

        headers = {

            "Content-Type":
            "application/json",

            "X-Auth-Token":
            token,

            "fiware-service":
            FIWARE_SERVICE,

            "fiware-servicepath":
            FIWARE_SERVICEPATH
        }

        # =========================================
        # PAYLOAD SENT TO ORION
        # =========================================

        payload = {

            "temperature": {

                "value":
                temperature,

                "type":
                "Float"
            },

            "humidity": {

                "value":
                humidity,

                "type":
                "Float"
            },

            "motion": {

                "value":
                motion,

                "type":
                "Boolean"
            },

            "distance": {

                "value":
                distance,

                "type":
                "Float"
            },

            "armed": {

                "value":
                armed,

                "type":
                "Boolean"
            },

            "alarm": {

                "value":
                alarm,

                "type":
                "Boolean"
            }
        }

        

        # =========================================
        # DEBUG INFO
        # =========================================
        print("\n========== FINAL DEBUG ==========")
        print("BROKER:",
      FIWARE_BROKER)
        print("SERVICE:",
      FIWARE_SERVICE)
        print("SERVICEPATH:",
      FIWARE_SERVICEPATH)
        print("URL:",
      url)
        print("HEADERS:",
      headers)
        print("PAYLOAD:",
      payload)
        print("=================================\n")


        # =========================================
        # SEND DATA TO ORION
        # =========================================

        response = requests.patch(
            url,
            json=payload,
            headers=headers,
            verify=False
        )

        # =========================================
        # DEBUG OUTPUT
        # =========================================

        print(
            "\n========== ORION DEBUG =========="
        )

        print(
            "STATUS:",
            response.status_code
        )

        print(
            "RESPONSE:",
            response.text
        )

        print(
            "=================================\n"
        )

        # =========================================
        # SUCCESS RESPONSE
        # =========================================

        return jsonify({

            "message":
            "Security Data Sent Successfully",

            "orion_status":
            response.status_code
        })

    except Exception as e:

        print(
            "\nBACKEND ERROR:",
            str(e)
        )

        return jsonify({

            "error":
            str(e)
        }), 500




# =====================================================
# MAIN
# =====================================================

if __name__ == '__main__':

    app.run(

        debug=True,

        host='0.0.0.0',

        port=5050
    )