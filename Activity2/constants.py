from enum import IntEnum

# I2C device addresses

LSM303D_Address = 0x1D  # Accelerometer & Magnetometer
L3GD20H_Address = 0x6B  # Gyroscope


class LSM303D(IntEnum):
    STATUS_M = 0x07
    OUT_X_L_M = 0x08
    OUT_X_H_M = 0x09
    OUT_Y_L_M = 0x0A
    OUT_Y_H_M = 0X0B
    OUT_Z_L_M = 0x0C
    OUT_Z_H_M = 0x0D
    WHO_AM_I = 0x0
    CTRL0 = 0x1F
    CTRL1 = 0x20
    CTRL2 = 0x21
    CTRL3 = 0x22
    CTRL4 = 0x23
    CTRL5 = 0x24
    CTRL6 = 0x25
    CTRL7 = 0x26
    STATUS_A = 0x2
    OUT_X_L_A = 0x28
    OUT_X_H_A = 0x29
    OUT_Y_L_A = 0x2A
    OUT_Y_H_A = 0x2B
    OUT_Z_L_A = 0x2C
    OUT_Z_H_A = 0x2D

class L3GD20H(IntEnum):
    WHO_AM_I_G = 0x0F
    CTRL1 = 0x20
    CTRL2 = 0x21
    CTRL3 = 0x22
    CTRL4 = 0x23
    CTRL5 = 0x24
    REFERENCE = 0x25
    OUT_TEMP = 0x26
    STATUS_G = 0x27
    OUT_X_L_G = 0x28
    OUT_X_H_G = 0x29
    OUT_Y_L_G = 0x2A
    OUT_Y_H_G = 0x2B
    OUT_Z_L_G = 0x2C
    OUT_Z_H_G = 0x2D
    FIFO_CTRL = 0x2E
    FIFO_SRC = 0x2F
    IG_CFG = 0x30
    IG_SRC = 0x31
    IG_THS_XH = 0x32
    IG_THS_XL = 0x33
    IG_THS_YH = 0x34
    IG_THS_YL = 0x35
    IG_THS_ZH = 0x36
    IG_THS_ZL = 0x37
    IG_DURATION = 0x38
    LOW_DR = 0x39