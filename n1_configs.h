#ifndef n1_config_h
#define n1_config_h

// Pins
#define R_PWM 9  //M1 Speed Control
#define L_PWM 11 //M2 Speed Control
#define R_DIR 8  //M1 Direction Control
#define L_DIR 10 //M1 Direction Control
#define R_ENC_OTHER 4 // Encoder Pin A
#define R_ENC_INT 2 // Int 0; Encode Pin B
#define L_ENC_INT 3 // Int 1; Encoder Pin A
#define L_ENC_OTHER 5 //Encode Pin B

// Buffers
#define CMDBUFFER 10 // Command buffer.

// Other
#define MAXSPEED 100 // In mm/s
#define BASEWIDTH 285 // in mm
#define WHEELDIAMETER 136 // in mm
#define N1_I2C_ADDR 0x10

#endif

