
#ifndef SERIAL_H
#define SERIAL_H

class SerialPort
{
public:
	SerialPort();

	void write(const char *s);

	bool available() const;

	char read();
};

#endif //SERIAL_H
