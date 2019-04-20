from AltIMU_v3 import AltIMUv3

altimu = AltIMUv3()
altimu.enable()

while True:
    accel = altimu.get_accelerometer_raw()
    print(accel)
    gyro = altimu.get_gyroscope_raw()
    print(gyro)