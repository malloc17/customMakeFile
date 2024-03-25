/*Başlangıç noktasını Reset Handler seçtik. Reset durumunda program buradan başlayacak.*/
ENTRY(Reset_Handler) 


/*This memory region is defined in STM32f407vg datasheet.*/
MEMORY {
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
	SRAM2 (rwx) : ORIGIN = 0x2001C000, LENGTH = 16K 
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
} 


SECTIONS
{
	.text : 
	{
		/*Tüm input file ların (all .o files) text alanlarını belirtmek için wildcard (*) karakteri kullanılır. */
		*(.isr_vector)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		/*Word ile align etmek için 4 yazılmalı*/
		. = ALIGN(4);
	
		/*Location counter show end of text section. I createrd _etext symbol and i assign this address to the symbol*/
		_etext = .;
		
		/*LMA (load mem addres) ve VMA (virtual mem addres) (embedded cihaz için VMA geçerli değil). */
		/*Burada şu soru sorulmalı. Bu section memory nin bir bölgesine load edilecek. Load edilen yer ile run timeda kullanılacak yer birbirinden farklı olacak mı?  */
		/*Örneğin .data section için bu alanlar farklı. Ama text alanı sadece flash hafıza da tutulacak. Programın başlaması onun yerini değiştirmeyecek.*/
		/*VMA ve LMA aynı olduğu durumda sadece LMA yi yazmak yeterli olur*/
	}> FLASH
	
	_sdata_flash = LOADADDR(.data);
	.data :
	{
		/*_sdata VMA e göre değer alır. Yani burada SRAM1 in başlangıç adresini tutmuş olur.*/
		_sdata = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;
		/*LMA -> FLASH ancak bu bölüm init  te SRAM e taşınacak. absoulute adresi SRAM olmuş olacak.*/
	}> SRAM1 AT> FLASH
	
	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		/*Bss section içerisinde derleyici bazı init edilmemiş global değişkenleri opt yaparak COMMON section ına atar. */
		/*O sebeple linker file da bss içerisinde bu common alanı da tanımlanmalıdır. Yoksa _ebss sembolü yanlış bir adresi gösterebilir.*/
		*(.COMMON)   
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
		
	}> SRAM1
}