import serial
import time

SERIAL_PORT = 'COM3'   # Change to your actual port
BAUD_RATE = 9600       # Must match your GPS module
JS_FILE = 'where.js'
MAX_POINTS = 1000

def init_js_file():
    """Initialize the JS file with empty coordinates array"""
    with open(JS_FILE, 'w') as f:
        f.write("function getAddressPoints() {\n    return [\n    ];\n}\n")

def update_js_file(coordinates):
    """Update the JS file with all coordinates"""
    with open(JS_FILE, 'w') as f:
        f.write("function getAddressPoints() {\n    return [\n")
        for lat, lng in coordinates:
            f.write(f"        [{lat:.6f}, {lng:.6f}],\n")
        f.write("    ];\n}\n")

def main():
    coordinates = []  # Store all coordinates in memory
    init_js_file()
    
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2)  # Wait for serial connection
        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud")
        print("Waiting for GPS data in format: latitude\\nlongitude\\n")

        while True:
            try:
                # Read raw data
                lat_line = ser.readline().decode().strip()
                lng_line = ser.readline().decode().strip()
                
                print(f"Raw data - Lat: '{lat_line}', Lng: '{lng_line}'")  # Debug

                # Skip empty lines
                if not lat_line or not lng_line:
                    continue

                # Convert to numbers
                try:
                    lat = float(lat_line)
                    lng = float(lng_line)
                except ValueError:
                    print(f"Invalid numbers: '{lat_line}', '{lng_line}'")
                    continue

                # Validate coordinates
                if not (-90 <= lat <= 90) or not (-180 <= lng <= 180):
                    print(f"Invalid coordinates: {lat}, {lng}")
                    continue

                # Add to memory and update file
                coordinates.append((lat, lng))
                update_js_file(coordinates)
                print(f"Added point {len(coordinates)}: {lat:.6f}, {lng:.6f}")

                # Reset if reached max points
                if len(coordinates) >= MAX_POINTS:
                    coordinates = []
                    init_js_file()
                    print("Reset coordinates storage")

            except Exception as e:
                print(f"Error processing data: {str(e)}")

    except serial.SerialException as e:
        print(f"Serial port error: {str(e)}")
    except KeyboardInterrupt:
        print("\nScript stopped by user")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()
