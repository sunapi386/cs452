ENTRY (main)

MEMORY
{
ram : ORIGIN = 0x00002100, LENGTH = 32M /* Offset by 0x2100 */
rom : ORIGIN = 0x60000000, LENGTH = 8M
}

SECTIONS
{
data : /* Initialized data. */
{
_DataStart = . ;
*(.data)
_DataEnd = . ;
} >ram

bss : /* Uninitialized data. */
{
_BssStart = . ;
*(.bss)
_BssEnd = . ;
} >ram

text : /* The actual instructions. */
{
*(.text)
*(.got)
*(.got.plt)
*(.rodata)
*(.glue_7)
*(.glue_7t)
} >ram
}
