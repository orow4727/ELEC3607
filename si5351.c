#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <Si5351A-RevB-Registers.h>

#define	I2C_FNAME	"/dev/i2c-2"
#define	SI5351_ADDR	0x60


int	i2c_file,i,j;

void i2c_init()
{
	i2c_file = open(I2C_FNAME, O_RDWR);
	if (i2c_file < 0)
		exit(1);
}

int i2c_read(unsigned char reg)
{
	if (ioctl(i2c_file, I2C_SLAVE, SI5351_ADDR) < 0) 
		exit(1);

	int res;

	/* Using SMBus commands */
	res = i2c_smbus_read_byte_data(i2c_file, reg);
	if (res < 0) 
		exit(1);
	else 
		printf("r dev(0x%x) reg(0x%x)=0x%x\n", SI5351_ADDR, reg, res);
	return res;
}

int i2c_write(unsigned char reg,int val)
{
	i2c_smbus_write_byte_data(i2c_file, reg, val);

}

int
main()
{
	i2c_init();
	i2c_read(0);

	i2c_write(3, 0xFF); //disable all outputs

	//pull down all driver outputs
	i = 0x00F1; //start register 16 -23
	while (i <= 0x0017)
	{
		i2c_write(i,0x80);
		i = i + 0x0001;
	}
	//set interrupt masks
	i2c_write(0x0002,0xF4); //0b11111000

	//write registers 15-92 and 149-170
	j=0;
	while (j < 52)
	{
		printf("%d", si5351a_revb_registers[1].address);
		//i2c_write(SI5351A_REVB_REG_CONFIG_NUM_REGS[i]);
		j +=1;
	}
}