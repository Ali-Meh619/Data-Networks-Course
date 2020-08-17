#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/applications-module.h"
#include "ns3/animation-interface.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/flow-monitor-module.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace ns3;

 

int main (int argc, char *argv[])
{

NS_LOG_COMPONENT_DEFINE ("Lab3_part2");
	
uint32_t PacketSize = 512; // bytes
std::string DataRate ("1Mbps");
uint16_t num_Nodes = 9;
uint16_t UDPport = 9;
bool tracing = false;


CommandLine cmd;
    cmd.AddValue("PacketSize", "size of application packet sent", PacketSize);
    cmd.AddValue("DataRate", "rate of pacekts sent", DataRate);
    cmd.AddValue("tracing", "turn on ascii and pcap tracing", tracing);
    cmd.Parse(argc, argv);


    Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(PacketSize));
    Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue(DataRate));
    Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));

    ns3::PacketMetadata::Enable();
    std::string animFile = "lab3_part2.xml";

    NodeContainer nodes;
    nodes.Create(num_Nodes);


NodeContainer AB = NodeContainer(nodes.Get (0),nodes.Get (1));
NodeContainer BC = NodeContainer(nodes.Get (1),nodes.Get (2));
NodeContainer CD = NodeContainer(nodes.Get (2),nodes.Get (3));
NodeContainer DE = NodeContainer(nodes.Get (3),nodes.Get (4));
NodeContainer EF = NodeContainer(nodes.Get (4),nodes.Get (5));
NodeContainer FG = NodeContainer(nodes.Get (5),nodes.Get (6));
NodeContainer GH = NodeContainer(nodes.Get (6),nodes.Get (7));
NodeContainer HA = NodeContainer(nodes.Get (7),nodes.Get (0));
NodeContainer BH = NodeContainer(nodes.Get (1),nodes.Get (7));
NodeContainer DF = NodeContainer(nodes.Get (3),nodes.Get (5));
NodeContainer BI = NodeContainer(nodes.Get (1),nodes.Get (8));
NodeContainer CI = NodeContainer(nodes.Get (2),nodes.Get (8));
NodeContainer DI = NodeContainer(nodes.Get (3),nodes.Get (8));
NodeContainer FI = NodeContainer(nodes.Get (5),nodes.Get (8));
NodeContainer GI = NodeContainer(nodes.Get (6),nodes.Get (8));
NodeContainer HI = NodeContainer(nodes.Get (7),nodes.Get (8));


PointToPointHelper p2p;
p2p.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
p2p.SetChannelAttribute ("Delay", StringValue ("10ms"));
NetDeviceContainer dAB = p2p.Install (AB);
NetDeviceContainer dBC = p2p.Install (BC);
NetDeviceContainer dCD = p2p.Install (CD);
NetDeviceContainer dDE = p2p.Install (DE);
NetDeviceContainer dEF = p2p.Install (EF);
NetDeviceContainer dFG = p2p.Install (FG);
NetDeviceContainer dGH = p2p.Install (GH);
NetDeviceContainer dHA = p2p.Install (HA);
NetDeviceContainer dBH = p2p.Install (BH);
NetDeviceContainer dDF = p2p.Install (DF);
NetDeviceContainer dBI = p2p.Install (BI);
NetDeviceContainer dCI = p2p.Install (CI);
NetDeviceContainer dDI = p2p.Install (DI);
NetDeviceContainer dFI = p2p.Install (FI);
NetDeviceContainer dGI = p2p.Install (GI);
NetDeviceContainer dHI = p2p.Install (HI);



NS_LOG_INFO("Setting routing protocols");
Ipv4StaticRoutingHelper staticRouting;
Ipv4GlobalRoutingHelper globalRouting;
Ipv4ListRoutingHelper list;
list.Add(staticRouting,0);
list.Add(globalRouting,10);
// Install network stacks on the nodes
InternetStackHelper internet;
internet.SetRoutingHelper(list);
internet.Install(nodes);


Ipv4AddressHelper ipv4;
ipv4.SetBase ("10.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer iAB = ipv4.Assign (dAB);
iAB.SetMetric(0,1);
iAB.SetMetric(1,1);
ipv4.SetBase ("10.1.2.0", "255.255.255.0");
Ipv4InterfaceContainer iBC = ipv4.Assign (dBC);
iBC.SetMetric(0,3);
iBC.SetMetric(1,3);
ipv4.SetBase ("10.1.3.0", "255.255.255.0");
Ipv4InterfaceContainer iCD = ipv4.Assign (dCD);
iCD.SetMetric(0,6);
iCD.SetMetric(1,6);
ipv4.SetBase ("10.1.4.0", "255.255.255.0");
Ipv4InterfaceContainer iDE = ipv4.Assign (dDE);
iDE.SetMetric(0,2);
iDE.SetMetric(1,2);
ipv4.SetBase ("10.1.5.0", "255.255.255.0");
Ipv4InterfaceContainer iEF = ipv4.Assign (dEF);
iEF.SetMetric(0,3);
iEF.SetMetric(1,3);
ipv4.SetBase ("10.1.6.0", "255.255.255.0");
Ipv4InterfaceContainer iFG = ipv4.Assign (dFG);
iFG.SetMetric(0,2);
iFG.SetMetric(1,2);
ipv4.SetBase ("10.1.7.0", "255.255.255.0");
Ipv4InterfaceContainer iGH = ipv4.Assign (dGH);
iGH.SetMetric(0,5);
iGH.SetMetric(1,5);
ipv4.SetBase ("10.1.8.0", "255.255.255.0");
Ipv4InterfaceContainer iHA = ipv4.Assign (dHA);
iHA.SetMetric(0,2);
iHA.SetMetric(1,2);
ipv4.SetBase ("10.1.9.0", "255.255.255.0");
Ipv4InterfaceContainer iBH = ipv4.Assign (dBH);
iBH.SetMetric(0 ,7);
iBH.SetMetric(1,7);
ipv4.SetBase ("10.1.10.0", "255.255.255.0");
Ipv4InterfaceContainer iDF = ipv4.Assign (dDF);
iDF.SetMetric(0,1);
iDF.SetMetric(1,1);
ipv4.SetBase ("10.1.11.0", "255.255.255.0");
Ipv4InterfaceContainer iBI = ipv4.Assign (dBI);
iBI.SetMetric(0,2);
iBI.SetMetric(1,2);
ipv4.SetBase ("10.1.12.0", "255.255.255.0");
Ipv4InterfaceContainer iCI = ipv4.Assign (dCI);
iCI.SetMetric(0,5);
iCI.SetMetric(1,5);
ipv4.SetBase ("10.1.13.0", "255.255.255.0");
Ipv4InterfaceContainer iDI = ipv4.Assign (dDI);
iDI.SetMetric(0,4);
iDI.SetMetric(1,4);
ipv4.SetBase ("10.1.14.0", "255.255.255.0");
Ipv4InterfaceContainer iFI = ipv4.Assign (dFI);
iFI.SetMetric(0,2);
iFI.SetMetric(1,2);
ipv4.SetBase ("10.1.15.0", "255.255.255.0");
Ipv4InterfaceContainer iGI = ipv4.Assign (dGI);
iGI.SetMetric(0,1);
iGI.SetMetric(1,1);
ipv4.SetBase ("10.1.16.0", "255.255.255.0");
Ipv4InterfaceContainer iHI = ipv4.Assign (dHI);
iHI.SetMetric(0,3);
iHI.SetMetric(1,3);

Ipv4GlobalRoutingHelper::PopulateRoutingTables ();





PacketSinkHelper UDPsink ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), UDPport));
ApplicationContainer App;
NodeContainer SourceNode = NodeContainer (nodes.Get (0));
NodeContainer SinkNode = NodeContainer (nodes.Get (4));



App = UDPsink.Install (SinkNode);
App.Start (Seconds (0.0));
App.Stop (Seconds (10.0));
Address D_Address(InetSocketAddress(iEF.GetAddress (0), UDPport));


OnOffHelper UDPsource ("ns3::UdpSocketFactory", D_Address);
UDPsource.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
UDPsource.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
UDPsource.Install(SourceNode);
App.Start (Seconds (1.0));
App.Stop (Seconds (10.0));



AnimationInterface anim (animFile);
Ptr<Node> n = nodes.Get (0);
anim.SetConstantPosition (n, 0, 20);
n = nodes.Get(1);
anim.SetConstantPosition(n,10,10);
n = nodes.Get(2);
anim.SetConstantPosition(n,20,0);
n = nodes.Get(3);
anim.SetConstantPosition(n,30,10);
n = nodes.Get(4);
anim.SetConstantPosition(n,40,20);
n = nodes.Get(5);
anim.SetConstantPosition(n,30,30);
n = nodes.Get(6);
anim.SetConstantPosition(n,20,40);
n = nodes.Get(7);
anim.SetConstantPosition(n,10,30);
n = nodes.Get(8);
anim.SetConstantPosition(n,20,20);

if (tracing == false)
{
AsciiTraceHelper ascii;
p2p.EnableAsciiAll (ascii.CreateFileStream ("Lab3_part2.tr"));
p2p.EnablePcapAll ("Lab3_part2");
}

Ptr<OutputStreamWrapper> stream1 = Create<OutputStreamWrapper> ("Table2", std::ios::out);
Ipv4GlobalRoutingHelper helper2;
helper2.PrintRoutingTableAllAt(Seconds(2.0),stream1);


  Simulator::Stop (Seconds (10.0));
 Simulator::Run ();
 Simulator::Destroy ();








 return 0; 


}
