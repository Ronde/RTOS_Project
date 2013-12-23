/** @file lis302dl_regs.h
 * @author 
 * LIS302 register description macros
 */


#define STATUS_REG      0x27
#define OUT_X          0x29
#define OUT_Y          0x2B
#define OUT_Z          0x2D

#define CTRL_REG1        0x20
#define CTRL_REG1_XEN    (1<<0)
#define CTRL_REG1_YEN    (1<<1)
#define CTRL_REG1_ZEN    (1<<2)
/*Scale selection*/
#define CTRL_REG1_FSEN   (1<<5)
/*Power down*/
#define CTRL_REG1_PDEN   (1<<6)

