from smbus import SMBus


class I2C(object):
    """
    I2C Wrapper.
    Provides helper methods for SMBus class used on a Raspberry Pi.
    """

    # Base Methods

    def __init__(self, bus_id=1):
        """
        Initialize the I2C bus.
        """
        self._i2c = SMBus(bus_id)

    def __del__(self):
        """
        Clean up.
        """
        try:
            del self._i2c
        except:
            pass

    # Reading and Writing Registers

    def write_register(self, address, register, value):
        """
        Write a single byte to a I2C register. Return the value the
        register had before the write.
        :param address: The I2C address of the device.
        :type address: int
        :param register: The register of the device.
        :type register: int
        :param value: The value to write.
        :type value: int
        """
        self._i2c.write_byte_data(address, register, value)

    def read_register(self, address, register):
        """
        Read a single I2C register.
        :param address: The I2C address of the device.
        :type address: int
        :param register: The register of the device.
        :type register: int
        :return: The value of the register.
        :rtype: int
        """
        return self._i2c.read_byte_data(address, register)

    # Getting Values

    def get_unsigned_value_from_bytes(self, low_byte, high_byte):
        """
        Combine low and high bytes to an unsigned 16 bit value.
        :param low_byte: The low byte of a 16 bit value.
        :type low_byte: int
        :param high_byte: The high byte of a 16 bit value.
        :type high_byte: int
        :return: An unsigned value from two bytes.
        :rtype: int
        """
        return ((high_byte & 0x00FF) << 8) | (low_byte & 0x00FF)

    def get_signed_value_from_bytes(self, low_byte, high_byte):
        """
        Combine low and high bytes to an signed 16 bit value.
        :param low_byte: The low byte of a 16 bit value.
        :type low_byte: int
        :param high_byte: The high byte of a 16 bit value.
        :type high_byte: int
        :return: A signed value from two bytes.
        :rtype: int
        """
        unsigned_value = self.get_unsigned_value_from_bytes(low_byte, high_byte)
        return self.twos_complement(unsigned_value)

    def twos_complement(self, value, bits=16):
        """
        Compute the 2's complement of a given value
        :param value: The value.
        :type value: int
        :param bits: The number of bits of the value. Defaulted to 16 bits.
        :type bits: int
        :return: The two's complement of a given value.
        :rtype: int
        """
        if (value & (1 << (bits - 1))) != 0:
            value = value - (1 << bits)
        return value

    # Reading 3D Sensor

    def read_sensor(self, address, registers):
        """
        Read vector of the given sensor.
        :param address: The address of the device.
        :type address: int
        :param registers: A list of registers to read.
        :type registers: [int]
        :return: A vector representing the device measurement.
        :rtype: [int]
        """

        # Read all the registers
        x_low = self.read_register(address, registers[0])
        x_hi = self.read_register(address, registers[1])
        y_low = self.read_register(address, registers[2])
        y_hi = self.read_register(address, registers[3])
        z_low = self.read_register(address, registers[4])
        z_hi = self.read_register(address, registers[5])

        # Combine the low and high bytes into signed numbers
        x_val = self.get_signed_value_from_bytes(x_low, x_hi)
        y_val = self.get_signed_value_from_bytes(y_low, y_hi)
        z_val = self.get_signed_value_from_bytes(z_low, z_hi)

        return [x_val, y_val, z_val]