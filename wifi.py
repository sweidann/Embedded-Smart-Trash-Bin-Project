import network
import time
import umail
import machine

# Wi-Fi credentials
SSID = "Vodafone-27E7"
PASSWORD = "67670636"

# Gmail SMTP server settings
SMTP_SERVER = "smtp.gmail.com"
SENDER_EMAIL = "embeddedproject78@gmail.com"
SENDER_APP_PASSWORD = "fpnvxtyoieyvzvtp"  # App Password
RECIPIENT_EMAIL = "mohamedhegazyy03@gmail.com"

# Signal Pins
SIGNAL_PIN = 15
FIRE_SIGNAL_PIN = 21

signal_pin = machine.Pin(SIGNAL_PIN, machine.Pin.IN, machine.Pin.PULL_DOWN)
fire_signal_pin = machine.Pin(FIRE_SIGNAL_PIN, machine.Pin.IN, machine.Pin.PULL_DOWN)

# Connect to Wi-Fi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)

    while not wlan.isconnected():
        print("Attempting to connect to Wi-Fi...")
        wlan.connect(SSID, PASSWORD)

        retries = 10
        while not wlan.isconnected() and retries > 0:
            print("Connecting to Wi-Fi...")
            time.sleep(1)
            retries -= 1

        if wlan.isconnected():
            print("Wi-Fi Connected!")
            print("Network configuration:", wlan.ifconfig())
            break
        else:
            print("Failed to connect to Wi-Fi. Retrying in 5 seconds...")
            time.sleep(5)

# Send email using SMTP with retry logic
def send_email(subject, body):
    success = False
    while not success:
        try:
            smtp = umail.SMTP(SMTP_SERVER, 465, ssl=True)
            smtp.login(SENDER_EMAIL, SENDER_APP_PASSWORD)
            print("Connected to SMTP server")

            smtp.to(RECIPIENT_EMAIL)
            smtp.write(f"From: {SENDER_EMAIL}\r\n")
            smtp.write(f"To: {RECIPIENT_EMAIL}\r\n")
            smtp.write(f"Subject: {subject}\r\n")
            smtp.write("\r\n")
            smtp.write(body)

            smtp.send()
            smtp.quit()
            print("Email sent successfully!")
            success = True
        except Exception as e:
            print(f"Failed to send email: {e}. Retrying in 5 seconds...")
            time.sleep(5)

# Main function
def main():
    while True:
        # Ensure Wi-Fi connection
        connect_wifi()

        # Example: Send email when signal pin is active
        if signal_pin.value() == 1:
            print("Basket is full! Sending email...")
            send_email("Basket Full", "Please empty the basket.")

        elif fire_signal_pin.value() == 1:
            print("Fire detected! Sending email...")
            send_email("Fire Alert!", "Check your basket for a fire!")

        time.sleep(1)  # Delay for the next check

# Run the program
main()
