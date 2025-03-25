/*  main.c
 *  modified from example/eeprom_bitbang.c
 *  Thanks to Steve Brown <sbrown@ewol.com> for the information how to do it.

 *  The top nibble controls input/output
 *  the bottom nibble controls the state of the lines set to output.
 *  The datasheet isn't clear what happens if you set a bit
 *  in the output register when that line is conditioned as input.
 *  This is described in more detail in the FT232R bitbang app note.
 *
 *  --BITMASK--
 *  CBUS Bits
 *  3210 3210
 *  xxxx xxxx
 *      |----|  Set Output Control [0->LO, 1->HI]
 * |----|       Cfg  Input/Output  [0->Input, 1->Output]
 *
 *  Example:
 *  All pins to output with 0 bit high: 0xF1 (11110001)
 *  Bits 0 and 1 to input, 2 and 3 to output and masked high: 0xCC (11001100)
 *      0x8C turn cbus[3] high by itself
 *      0x4C turn cbus[2] high by itself
 *
 *  The input is standard "0x" hex notation.
 *  A carriage return terminates the program.
 *
 *  This program is distributed under the GPL, version 2
 *
 *  SEQUENCE: Enter BootLoader Mode: Cbus[3]=BOOT0, Cbus[2]=RST (ignore CBUS1 and CBUS0 as inputs)
 *  Note: Cbus[2]=RST drives an inversion of uC-nRst
 *  0xCC - BOOT0-High and RST-High  = BootLoader-Mode in Reset
 *  0xC8 - BOOT0-High, RST-Low      = Bootloader-Mode RUN
 *  0x00 - CBUS all inputs          = Continue running (Reset-PullUp, Boot0-pullDown)
 *  ----
 *  0xC4 - BOOT0-LOW, RST-High     = Normal-Mode - in Reset
 *  0xC0 - BOOT0-LOW, RST-LOW       = Normal-Mode - RUN (pins driven)
 *  0x00 - CBUS all inputs          = Continue running (Reset-PullUp, Boot0-pullDown)
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ftdi.h>

int main(void)
{
    struct ftdi_context *ftdi;
    int err;
    unsigned char buf[1];
    unsigned char bitmask;
    char input[10];

    if ((ftdi = ftdi_new()) == 0)
    {
        fprintf(stderr, "ftdi_new failed\n");
        return EXIT_FAILURE;
    }

    err = ftdi_usb_open_desc(ftdi, 0x0403, 0x6001, "FT232R USB UART", NULL);    // Use Description specific string(default for chip used on board)
    if (err < 0 && err != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", err, ftdi_get_error_string(ftdi));
        ftdi_free(ftdi);
        exit(-1);
    }
    printf("ftdi open succeeded: %d\n", err);

    while (1)
    {
        // Set bitmask from input
        char *s = fgets(input, sizeof(input) - 1, stdin);
        if (s == NULL || input[0] == '\n')
            break;
        bitmask = strtol(input, NULL, 0);
        printf("Using bitmask 0x%02x\n", bitmask);
        err = ftdi_set_bitmode(ftdi, bitmask, BITMODE_CBUS);
        if (err < 0)
        {
            fprintf(stderr, "set_bitmode failed for 0x%x, error %d (%s)\n", bitmask, err, ftdi_get_error_string(ftdi));
            ftdi_usb_close(ftdi);
            ftdi_free(ftdi);
            exit(-1);
        }

        // read CBUS
        err = ftdi_read_pins(ftdi, &buf[0]);
        if (err < 0)
        {
            fprintf(stderr, "read_pins failed, error %d (%s)\n", err, ftdi_get_error_string(ftdi));
            ftdi_usb_close(ftdi);
            ftdi_free(ftdi);
            exit(-1);
        }
        printf("Read returned 0x%01x\n", buf[0] & 0x0f);
    }
    printf("disabling bitbang mode\n");
    ftdi_disable_bitbang(ftdi); // reset to regular serial/FIFO
    ftdi_usb_close(ftdi);       // close the ftdi device, releases to kernel
    ftdi_free(ftdi);            // deallocate ftdi context

    return 0;
}
