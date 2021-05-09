#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#define	I2C_FNAME	"/dev/i2c-2"
#define	SI5351_ADDR	0x60

#define SI5351A_REVB_REG_CONFIG_NUM_REGS				53

typedef struct
{
	unsigned int address; /* 16-bit register address */
	unsigned char value; /* 8-bit register data */

} si5351a_revb_register_t;

si5351a_revb_register_t const si5351a_revb_registers[SI5351A_REVB_REG_CONFIG_NUM_REGS] =
{
	
	{ 0x0002, 0x53 },
	{ 0x0003, 0x00 },
	{ 0x0004, 0x20 },
	{ 0x0007, 0x00 },
	{ 0x000F, 0x00 },
	{ 0x0010, 0x0F },
	{ 0x0011, 0x0F },
	{ 0x0012, 0x8C },
	{ 0x0013, 0x8C },
	{ 0x0014, 0x8C },
	{ 0x0015, 0x8C },
	{ 0x0016, 0x8C },
	{ 0x0017, 0x8C },
	{ 0x001A, 0x17 },
	{ 0x001B, 0x70 },
	{ 0x001C, 0x00 },
	{ 0x001D, 0x0E },
	{ 0x001E, 0xA9 },
	{ 0x001F, 0x00 },
	{ 0x0020, 0x02 },
	{ 0x0021, 0x90 },
	{ 0x002A, 0x00 },
	{ 0x002B, 0x04 },
	{ 0x002C, 0x00 },
	{ 0x002D, 0x3D },
	{ 0x002E, 0x60 },
	{ 0x002F, 0x00 },
	{ 0x0030, 0x00 },
	{ 0x0031, 0x00 },
	{ 0x0032, 0x00 },
	{ 0x0033, 0x04 },
	{ 0x0034, 0x00 },
	{ 0x0035, 0x3D },
	{ 0x0036, 0x60 },
	{ 0x0037, 0x00 },
	{ 0x0038, 0x00 },
	{ 0x0039, 0x00 },
	{ 0x005A, 0x00 },
	{ 0x005B, 0x00 },
	{ 0x0095, 0x00 },
	{ 0x0096, 0x00 },
	{ 0x0097, 0x00 },
	{ 0x0098, 0x00 },
	{ 0x0099, 0x00 },
	{ 0x009A, 0x00 },
	{ 0x009B, 0x00 },
	{ 0x00A2, 0x00 },
	{ 0x00A3, 0x00 },
	{ 0x00A4, 0x00 },
	{ 0x00A5, 0x00 },
	{ 0x00A6, 0xE0 },
	{ 0x00B7, 0x92 },
	
};


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
	i2c_write(0x0003, 0xFF); //disable all outputs
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
	while (j <= 52)
	{
		i2c_write(si5351a_revb_registers[j].address,si5351a_revb_registers[j].value);
		//printf("%d\n", j );
		j +=1;
	}
	//Apply PLL A and B soft reset
	i2c_write(0x00B1,0xAC);
	//enable output
	i2c_write(0x0003, 0x00);
}