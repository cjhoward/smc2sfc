# SMC2SFC

This is a small utility program which converts SNES ROMs in SMC/SWC formats to SFC by stripping the headers from the files. Input files which do not contain SMC/SWC headers will simply be copied.

## Building

	g++ smc2sfc.cpp -o smc2sfc

## Usage

	smc2sfc <input> <output>

## License

The source code to SMC2SFC is licensed under the GNU General Public License, version 3. See [COPYING](COPYING) for details.
