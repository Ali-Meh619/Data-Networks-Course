#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/address.h"
#include "ns3/udp-echo-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/flow-monitor.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;
int main (int argc, char *argv[])
{
	CommandLine cmd;
	cmd.Parse (argc, argv);

        char flowname[32];
	char animname[32];
	char pcapname[32];
        int v=1;
        //abcdefgh
        //96102331


        

        sprintf(flowname,"flow%dkB_%.2d.xml",512,6);
	sprintf(animname,"anim%dkB_%.2d.xml",512,6);
	sprintf(pcapname,"pcap%dkB",512);
	NodeContainer csmaNodes;
	csmaNodes.Create(8);
	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", StringValue ("1024kbps"));
	csma.SetChannelAttribute ("Delay", StringValue ("2ms"));
	NetDeviceContainer csmaDevices;
	csmaDevices = csma.Install (csmaNodes);
        if(v==0)csma.EnablePcapAll (pcapname);
	InternetStackHelper stack;
	stack.Install(csmaNodes);
	Ipv4AddressHelper address;
	address.SetBase ("20.5.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces;
	csmaInterfaces = address.Assign (csmaDevices);
	
        float datarate[7] = {16 + 9.5 , 32 + 5.1 , 64 + 1 , 128 + 0.2 , 256 + 20 , 512 + 5 , 1024 + 51};
        
	float packetSize = 512;
        float interval= packetSize * 8 / (datarate[6]*1024);

	UdpEchoServerHelper echoServer1(3);
	ApplicationContainer serverApps1 = echoServer1.Install (csmaNodes.Get (0));
	serverApps1.Start (Seconds (1.0));
        serverApps1.Stop (Seconds (10.0));

	
	UdpEchoClientHelper echoClient1 (csmaInterfaces.GetAddress (0), 3);
        echoClient1.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient1.SetAttribute ("Interval", TimeValue (Seconds (interval)));
        echoClient1.SetAttribute ("PacketSize", UintegerValue (512));

        ApplicationContainer clientApps1 = echoClient1.Install (csmaNodes.Get (4));
        clientApps1.Start (Seconds (1.0));
        clientApps1.Stop (Seconds (11.0));





	UdpEchoServerHelper echoServer2(3);
	ApplicationContainer serverApps2 = echoServer2.Install (csmaNodes.Get (1));
	serverApps2.Start (Seconds (1.0));
        serverApps2.Stop (Seconds (10.0));

	
	UdpEchoClientHelper echoClient2 (csmaInterfaces.GetAddress (1), 3);
        echoClient2.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient2.SetAttribute ("Interval", TimeValue (Seconds (interval)));
        echoClient2.SetAttribute ("PacketSize", UintegerValue (512));

        ApplicationContainer clientApps2 = echoClient2.Install (csmaNodes.Get (5));
        clientApps2.Start (Seconds (1.0));
        clientApps2.Stop (Seconds (11.0));






	UdpEchoServerHelper echoServer3(3);
	ApplicationContainer serverApps3 = echoServer3.Install (csmaNodes.Get (6));
	serverApps3.Start (Seconds (1.0));
        serverApps3.Stop (Seconds (10.0));

	
	UdpEchoClientHelper echoClient3 (csmaInterfaces.GetAddress (6), 3);
        echoClient3.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient3.SetAttribute ("Interval", TimeValue (Seconds (interval)));
        echoClient3.SetAttribute ("PacketSize", UintegerValue (512));

        ApplicationContainer clientApps3 = echoClient3.Install (csmaNodes.Get (2));
        clientApps3.Start (Seconds (1.0));
        clientApps3.Stop (Seconds (11.0));





	UdpEchoServerHelper echoServer4(3);
	ApplicationContainer serverApps4 = echoServer4.Install (csmaNodes.Get (7));
	serverApps4.Start (Seconds (1.0));
        serverApps4.Stop (Seconds (10.0));

	
	UdpEchoClientHelper echoClient4 (csmaInterfaces.GetAddress (7), 3);
        echoClient4.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient4.SetAttribute ("Interval", TimeValue (Seconds (interval)));
        echoClient4.SetAttribute ("PacketSize", UintegerValue (512));

        ApplicationContainer clientApps4 = echoClient4.Install (csmaNodes.Get (3));
        clientApps4.Start (Seconds (1.0));
        clientApps4.Stop (Seconds (11.0));
	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();






	Ptr<FlowMonitor> flowMonitor;
	FlowMonitorHelper flowHelper;
	flowMonitor = flowHelper.InstallAll();

        AnimationInterface::SetConstantPosition(csmaNodes.Get(0),10.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(1),20.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(2),30.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(3),40.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(4),50.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(5),60.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(6),70.0,0.0);
	AnimationInterface::SetConstantPosition(csmaNodes.Get(7),80.0,0.0);
        AnimationInterface anim (animname);



       Simulator::Stop (Seconds(20));

       Simulator::Run ();
       










       flowMonitor->SerializeToXmlFile(flowname, true, true);

        






        return 0;


}
