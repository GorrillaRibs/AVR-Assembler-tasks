#include <avr/io.h>
#include <ASCII.h>
/*
 Implemented functions r25,r24,... holds the parameter(s)
 initUART                   ; receives the 16-bit (r25:r24) value for UBRR0H:L
 printChar                  ; receives r25 transmits ASCII char
 printCharLn                ; calls printChar and appends the newline character
 printByte                  ; converts r25 to decimal ASCII characters and transmits
 printBin                   ; converts r25 to binary ASCII characters and transmits
 printHexChar               ; converts and transmits the base 16 equivalent of the low nibble of r25
 printHex                   ; converts r25 to hexadecimal ASCII characters and transmits
 printStr                   ; receives pointer (Z) to null-terminated string in progmem and calls printChar
 printStrLn                 ; same as printStr but appends newLine character
 printReg                   ; prints a single register contents defined by parameter: r(r25)=r24
 printGPRegs                ; scrolls through SRAM dumping all GP register contents
 printIORegs                ; scrolls through SRAM dumping all IO register contents
 printExRegs                ; scrolls through SRAM dumping all Extended register contents
 breakPoint                 ; dumps the contents of the GP registers and enters an infinite loop
 wait                       ; delay for 250ms

*/
.global initUART
initUART:
  sts UBRR0H, r25                 //The UBRR0H and L registers control the baud rate
  sts UBRR0L, r24                 //The UBRR0H and L registers control the baud rate
  ldi r16, 1<<TXEN0 | 1<<RXEN0    //These bits in the UCSR0B register enables transmitting functions if set (Pin 1 on the arduino uno)
                                  //and receiving functions if set (Pin 0 on the arduino uno)
                                  //Set both bits if you want to enable both (also disable UCSZ03)
  sts UCSR0B, r16                 //Set both even though we're only transmitting to serial monitor in this example
  ldi r16, 3 << UCSZ00            //Set the UCSZ00 and UCSZ01 bits so we get an 8 bit data size (enough for char)
  sts UCSR0C, r16                 //Data is 8 bit data size
 ret
