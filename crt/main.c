
static volatile char * const VIO0_IO  = (volatile char *)0x6000;
static volatile char * const VIO0_CFG = (volatile char *)0x6002;



int main( )
{
    *VIO0_CFG = 0xff;
    for(;;)
    {
        *VIO0_IO = 0x55;
        *VIO0_IO = 0xAA;
    }

    return 0;
}
