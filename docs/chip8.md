# Chip-8

Old Virtual Machine that is simpler than most other machines.

### Registers

V0 - VF
    - 16 (8 Bit) Registers
    - VF is used to hold result of operations

Index Registers
    - 16 bit to hold memory

Program Counter
    - Holds the current address
    - 16 bits to hold memory address
    - PC must be incremented before executing since it is often manipulated
    - Increment by two since each instruction is 2 bytes

Stack Pointer
    - Stack size is 16 levels deep
    - 8 Bits for 16 indices into a stack array

### Components

Delay Timer
    - 8 Bits
    - 60Hz decrement

Sound Timer
    - 8 Bits
    - 60Hz decrement
    - Simple Tone Buzz

16 Input Keys
    - 0 through F in hex
    - Pressed or not pressed

    A mapping example

    Keypad       Keyboard
    +-+-+-+-+    +-+-+-+-+
    |1|2|3|C|    |1|2|3|4|
    +-+-+-+-+    +-+-+-+-+
    |4|5|6|D|    |Q|W|E|R|
    +-+-+-+-+ => +-+-+-+-+
    |7|8|9|E|    |A|S|D|F|
    +-+-+-+-+    +-+-+-+-+
    |A|0|B|F|    |Z|X|C|V|
    +-+-+-+-+    +-+-+-+-+

Monochrome Display
    - 64x32 pixels
    - Pixel is on or off (two colors)
    
    Modes

    - Sprite Pixel Off XOR Display Pixel Off = Display Pixel Off
    - Sprite Pixel Off XOR Display Pixel On = Display Pixel On
    - Sprite Pixel On XOR Display Pixel Off = Display Pixel On
    - Sprite Pixel On XOR Display Pixel On = Display Pixel Off