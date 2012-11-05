
sample_test.elf:     file format elf32-i386

Disassembly of section .init:

08048230 <_init>:
 8048230:	55                   	push   %ebp
 8048231:	89 e5                	mov    %esp,%ebp
 8048233:	83 ec 08             	sub    $0x8,%esp
 8048236:	e8 61 00 00 00       	call   804829c <call_gmon_start>
 804823b:	e8 bc 00 00 00       	call   80482fc <frame_dummy>
 8048240:	e8 ab 01 00 00       	call   80483f0 <__do_global_ctors_aux>
 8048245:	c9                   	leave  
 8048246:	c3                   	ret    
Disassembly of section .plt:

08048248 <.plt>:
 8048248:	ff 35 b0 95 04 08    	pushl  0x80495b0
 804824e:	ff 25 b4 95 04 08    	jmp    *0x80495b4
 8048254:	00 00                	add    %al,(%eax)
 8048256:	00 00                	add    %al,(%eax)
 8048258:	ff 25 b8 95 04 08    	jmp    *0x80495b8
 804825e:	68 00 00 00 00       	push   $0x0
 8048263:	e9 e0 ff ff ff       	jmp    8048248 <_init+0x18>
 8048268:	ff 25 bc 95 04 08    	jmp    *0x80495bc
 804826e:	68 08 00 00 00       	push   $0x8
 8048273:	e9 d0 ff ff ff       	jmp    8048248 <_init+0x18>
Disassembly of section .text:

08048278 <_start>:
 8048278:	31 ed                	xor    %ebp,%ebp
 804827a:	5e                   	pop    %esi
 804827b:	89 e1                	mov    %esp,%ecx
 804827d:	83 e4 f0             	and    $0xfffffff0,%esp
 8048280:	50                   	push   %eax
 8048281:	54                   	push   %esp
 8048282:	52                   	push   %edx
 8048283:	68 bc 83 04 08       	push   $0x80483bc
 8048288:	68 8c 83 04 08       	push   $0x804838c
 804828d:	51                   	push   %ecx
 804828e:	56                   	push   %esi
 804828f:	68 28 83 04 08       	push   $0x8048328
 8048294:	e8 bf ff ff ff       	call   8048258 <_init+0x28>
 8048299:	f4                   	hlt    
 804829a:	90                   	nop    
 804829b:	90                   	nop    

0804829c <call_gmon_start>:
 804829c:	55                   	push   %ebp
 804829d:	89 e5                	mov    %esp,%ebp
 804829f:	53                   	push   %ebx
 80482a0:	50                   	push   %eax
 80482a1:	e8 00 00 00 00       	call   80482a6 <call_gmon_start+0xa>
 80482a6:	5b                   	pop    %ebx
 80482a7:	81 c3 06 13 00 00    	add    $0x1306,%ebx
 80482ad:	8b 83 14 00 00 00    	mov    0x14(%ebx),%eax
 80482b3:	85 c0                	test   %eax,%eax
 80482b5:	74 02                	je     80482b9 <call_gmon_start+0x1d>
 80482b7:	ff d0                	call   *%eax
 80482b9:	8b 5d fc             	mov    0xfffffffc(%ebp),%ebx
 80482bc:	c9                   	leave  
 80482bd:	c3                   	ret    
 80482be:	90                   	nop    
 80482bf:	90                   	nop    

080482c0 <__do_global_dtors_aux>:
 80482c0:	55                   	push   %ebp
 80482c1:	89 e5                	mov    %esp,%ebp
 80482c3:	83 ec 08             	sub    $0x8,%esp
 80482c6:	80 3d c4 95 04 08 00 	cmpb   $0x0,0x80495c4
 80482cd:	75 29                	jne    80482f8 <__do_global_dtors_aux+0x38>
 80482cf:	a1 cc 94 04 08       	mov    0x80494cc,%eax
 80482d4:	8b 10                	mov    (%eax),%edx
 80482d6:	85 d2                	test   %edx,%edx
 80482d8:	74 17                	je     80482f1 <__do_global_dtors_aux+0x31>
 80482da:	89 f6                	mov    %esi,%esi
 80482dc:	83 c0 04             	add    $0x4,%eax
 80482df:	a3 cc 94 04 08       	mov    %eax,0x80494cc
 80482e4:	ff d2                	call   *%edx
 80482e6:	a1 cc 94 04 08       	mov    0x80494cc,%eax
 80482eb:	8b 10                	mov    (%eax),%edx
 80482ed:	85 d2                	test   %edx,%edx
 80482ef:	75 eb                	jne    80482dc <__do_global_dtors_aux+0x1c>
 80482f1:	c6 05 c4 95 04 08 01 	movb   $0x1,0x80495c4
 80482f8:	c9                   	leave  
 80482f9:	c3                   	ret    
 80482fa:	89 f6                	mov    %esi,%esi

080482fc <frame_dummy>:
 80482fc:	55                   	push   %ebp
 80482fd:	89 e5                	mov    %esp,%ebp
 80482ff:	83 ec 08             	sub    $0x8,%esp
 8048302:	a1 a8 95 04 08       	mov    0x80495a8,%eax
 8048307:	85 c0                	test   %eax,%eax
 8048309:	74 19                	je     8048324 <frame_dummy+0x28>
 804830b:	b8 00 00 00 00       	mov    $0x0,%eax
 8048310:	85 c0                	test   %eax,%eax
 8048312:	74 10                	je     8048324 <frame_dummy+0x28>
 8048314:	83 ec 0c             	sub    $0xc,%esp
 8048317:	68 a8 95 04 08       	push   $0x80495a8
 804831c:	e8 df 7c fb f7       	call   0 <_init-0x8048230>
 8048321:	83 c4 10             	add    $0x10,%esp
 8048324:	c9                   	leave  
 8048325:	c3                   	ret    
 8048326:	90                   	nop    
 8048327:	90                   	nop    

08048328 <main>:
#include "serial.h"
#include "net.h"

int main( void )
{
 8048328:	55                   	push   %ebp
 8048329:	89 e5                	mov    %esp,%ebp
 804832b:	83 ec 08             	sub    $0x8,%esp
 804832e:	83 e4 f0             	and    $0xfffffff0,%esp
 8048331:	b8 00 00 00 00       	mov    $0x0,%eax
 8048336:	29 c4                	sub    %eax,%esp
	printf( "<main.c> main running! \n" );
 8048338:	83 ec 0c             	sub    $0xc,%esp
 804833b:	68 48 84 04 08       	push   $0x8048448
 8048340:	e8 23 ff ff ff       	call   8048268 <_init+0x38>
 8048345:	83 c4 10             	add    $0x10,%esp
	
	serial_test();
 8048348:	e8 0f 00 00 00       	call   804835c <serial_test>

	net_test();
 804834d:	e8 22 00 00 00       	call   8048374 <net_test>

	return 0;
 8048352:	b8 00 00 00 00       	mov    $0x0,%eax
}
 8048357:	c9                   	leave  
 8048358:	c3                   	ret    
 8048359:	90                   	nop    
 804835a:	90                   	nop    
 804835b:	90                   	nop    

0804835c <serial_test>:

#include <stdio.h>

void serial_test( void )
{
 804835c:	55                   	push   %ebp
 804835d:	89 e5                	mov    %esp,%ebp
 804835f:	83 ec 08             	sub    $0x8,%esp
	printf( "<serial.c> serial_test running! \n" );
 8048362:	83 ec 0c             	sub    $0xc,%esp
 8048365:	68 80 84 04 08       	push   $0x8048480
 804836a:	e8 f9 fe ff ff       	call   8048268 <_init+0x38>
 804836f:	83 c4 10             	add    $0x10,%esp
	return;
}
 8048372:	c9                   	leave  
 8048373:	c3                   	ret    

08048374 <net_test>:

#include <stdio.h>

void net_test( void )
{
 8048374:	55                   	push   %ebp
 8048375:	89 e5                	mov    %esp,%ebp
 8048377:	83 ec 08             	sub    $0x8,%esp
	printf( "<net.c> net_test running! \n" );
 804837a:	83 ec 0c             	sub    $0xc,%esp
 804837d:	68 a2 84 04 08       	push   $0x80484a2
 8048382:	e8 e1 fe ff ff       	call   8048268 <_init+0x38>
 8048387:	83 c4 10             	add    $0x10,%esp
	return;
}
 804838a:	c9                   	leave  
 804838b:	c3                   	ret    

0804838c <__libc_csu_init>:
 804838c:	55                   	push   %ebp
 804838d:	89 e5                	mov    %esp,%ebp
 804838f:	56                   	push   %esi
 8048390:	53                   	push   %ebx
 8048391:	e8 9a fe ff ff       	call   8048230 <_init>
 8048396:	b8 c4 94 04 08       	mov    $0x80494c4,%eax
 804839b:	2d c4 94 04 08       	sub    $0x80494c4,%eax
 80483a0:	c1 f8 02             	sar    $0x2,%eax
 80483a3:	31 db                	xor    %ebx,%ebx
 80483a5:	39 c3                	cmp    %eax,%ebx
 80483a7:	73 0f                	jae    80483b8 <__libc_csu_init+0x2c>
 80483a9:	89 c6                	mov    %eax,%esi
 80483ab:	90                   	nop    
 80483ac:	ff 14 9d c4 94 04 08 	call   *0x80494c4(,%ebx,4)
 80483b3:	43                   	inc    %ebx
 80483b4:	39 f3                	cmp    %esi,%ebx
 80483b6:	72 f4                	jb     80483ac <__libc_csu_init+0x20>
 80483b8:	5b                   	pop    %ebx
 80483b9:	5e                   	pop    %esi
 80483ba:	c9                   	leave  
 80483bb:	c3                   	ret    

080483bc <__libc_csu_fini>:
 80483bc:	55                   	push   %ebp
 80483bd:	89 e5                	mov    %esp,%ebp
 80483bf:	53                   	push   %ebx
 80483c0:	50                   	push   %eax
 80483c1:	b8 c4 94 04 08       	mov    $0x80494c4,%eax
 80483c6:	2d c4 94 04 08       	sub    $0x80494c4,%eax
 80483cb:	c1 f8 02             	sar    $0x2,%eax
 80483ce:	85 c0                	test   %eax,%eax
 80483d0:	8d 58 ff             	lea    0xffffffff(%eax),%ebx
 80483d3:	75 0b                	jne    80483e0 <__libc_csu_fini+0x24>
 80483d5:	8b 5d fc             	mov    0xfffffffc(%ebp),%ebx
 80483d8:	c9                   	leave  
 80483d9:	e9 36 00 00 00       	jmp    8048414 <_fini>
 80483de:	89 f6                	mov    %esi,%esi
 80483e0:	ff 14 9d c4 94 04 08 	call   *0x80494c4(,%ebx,4)
 80483e7:	89 da                	mov    %ebx,%edx
 80483e9:	4b                   	dec    %ebx
 80483ea:	85 d2                	test   %edx,%edx
 80483ec:	75 f2                	jne    80483e0 <__libc_csu_fini+0x24>
 80483ee:	eb e5                	jmp    80483d5 <__libc_csu_fini+0x19>

080483f0 <__do_global_ctors_aux>:
 80483f0:	55                   	push   %ebp
 80483f1:	89 e5                	mov    %esp,%ebp
 80483f3:	53                   	push   %ebx
 80483f4:	52                   	push   %edx
 80483f5:	a1 98 95 04 08       	mov    0x8049598,%eax
 80483fa:	83 f8 ff             	cmp    $0xffffffff,%eax
 80483fd:	bb 98 95 04 08       	mov    $0x8049598,%ebx
 8048402:	74 0c                	je     8048410 <__do_global_ctors_aux+0x20>
 8048404:	83 eb 04             	sub    $0x4,%ebx
 8048407:	ff d0                	call   *%eax
 8048409:	8b 03                	mov    (%ebx),%eax
 804840b:	83 f8 ff             	cmp    $0xffffffff,%eax
 804840e:	75 f4                	jne    8048404 <__do_global_ctors_aux+0x14>
 8048410:	58                   	pop    %eax
 8048411:	5b                   	pop    %ebx
 8048412:	c9                   	leave  
 8048413:	c3                   	ret    
Disassembly of section .fini:

08048414 <_fini>:
 8048414:	55                   	push   %ebp
 8048415:	89 e5                	mov    %esp,%ebp
 8048417:	53                   	push   %ebx
 8048418:	52                   	push   %edx
 8048419:	e8 00 00 00 00       	call   804841e <_fini+0xa>
 804841e:	5b                   	pop    %ebx
 804841f:	81 c3 8e 11 00 00    	add    $0x118e,%ebx
 8048425:	e8 96 fe ff ff       	call   80482c0 <__do_global_dtors_aux>
 804842a:	8b 5d fc             	mov    0xfffffffc(%ebp),%ebx
 804842d:	c9                   	leave  
 804842e:	c3                   	ret    
