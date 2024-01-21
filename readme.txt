This project is an emulator for a 8-bit CPU, specifically the MOS 6502 processor. I have been using these sites for reference: 

https://web.archive.org/web/20210501043555/http://www.obelisk.me.uk/6502/reference.html#LDA
https://www.masswerk.at/6502/6502_instruction_set.html
http://6502.org/ - plenty of resources, and you can find the datasheet here 

Useful for creating the lookup table, this site has all the illegal opcodes populated into the data sheet
- http://www.oxyron.de/html/opcodes02.html

This project is to increase my understanding of how a CPU works and the infamous 6502 processor was a easy way to start. It is important to note that this emulator will not by timing accurate, I am still checking to see if page boundary is crossed and incrementing clock cycles to add some accuracy. Additionally, this emulator will not currently handle illegal opcodes, instead it will be wrapped into one illegalOpcode function. 

Todo: 

- Decimal Mode

- Disassembler 