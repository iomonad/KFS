/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <kernel.h>

/* Initialize video buffer */
uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;
uint16_t vga_buffer_cursor = 0x00;
uint16_t vga_buffer_line_pos = 0x01;

void __kmain()
{
	vga_clear_screen();
	vga_puts("            ..                 ..\n");
	vga_puts("	   .:o,               .cd.\n");
	vga_puts("           l :0.             *c:*:\n");
	vga_puts("           l ;x;.          .;x* *c.\n");
	vga_puts("           l ..0;         .,o....:.\n");
	vga_puts("          .:.;.xc;;;;.   *ll ....:.\n");
	vga_puts("          :,:c..cdddd;...l:......:.\n");
	vga_puts("          ok, ..     :kkk;....*,.:.\n");
	vga_puts("       ..*d*.............xl...dd.:.\n");
	vga_puts("      ,oko ..............oo::0Kd.c.\n");
	vga_puts("    ..d,...    ....   ....;xK0kc*:\n");
	vga_puts("    ;k............. ........k0, *;.\n");
	vga_puts("    l............   .........d;...l\n");
	vga_puts("   .c..*c0K,..... .,;........ cd;.c.\n");
	vga_puts("   l.  c;0d*......,x0c.........:k..c\n");
	vga_puts("  .l.  :;o ......ld*O0d........;x:.c.\n");
	vga_puts("  .:   ..........c;K0kc...   ....x*l.\n");
	vga_puts("  ,, . *;;.......:,kk, ...   .... oO.\n");
	vga_puts("  c ...d0k.............       .....l.\n");
	vga_puts(" *c..*k0OOK:...,.......       .....c*\n");
	vga_puts(" x,ccc.dl*Kx ..d;..            .... l\n");
	vga_puts("  .  cK000Od:l  ...            .... l.\n");
	vga_puts(" ;,..cx;Oo.................. .......,,\n");
	vga_puts(" ;,..c**: ..cOk.oc.......... .......:,\n");
	vga_puts(" ;,...dx:.................... .. .. l\n");
	vga_puts(" ,;...  ;OO:,,;k;............ ......c\n");
	vga_puts("  c .......oxxd........ .... ......l.\n");
	vga_puts("  c........    ............. .. ...o.\n");
	vga_puts("  .c.................... ..........c\n");
	vga_puts("  .l*................... .....oo..,:\n");
	vga_puts("   :l............... .. ..........l\n");
	vga_puts("    .O:................ ...,O....;l\n");
	vga_puts("     .x,..............   oc......O.\n");
	vga_puts("       lo*........,,,oOOO. ...*cd\n");
	vga_puts("        ;d       :kOk:......  ll\n");
	vga_puts("         .OOOOOOO:    ...*,:OO*\n");
	vga_puts("            .............dko\n");
	vga_puts("            .............\n");
	return ;
}
