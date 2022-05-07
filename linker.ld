ENTRY(_start)

SECTIONS
{
	. = 1M;
	_kernel_start = .;
	.boot ALIGN(4K) :
	{
		*(.multiboot)
		*(.boot)
	}

	. += 0xE0000000;
	.text ALIGN(4K) : AT (ADDR (.text) - 0xE0000000)
	{
		*(.text)
	}

	.rodata ALIGN(4K) : AT (ADDR (.rodata) - 0xE0000000)
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT (ADDR (.data) - 0xE0000000)
	{
		*(.data)
	}

	.bss ALIGN(4K) : AT (ADDR (.bss) - 0xE0000000)
	{
		*(.bss)
		*(COMMON)
	}
	_kernel_end = . - 0xE0000000;
}