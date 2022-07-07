#include"ns3/netanim-module.h"
#include"ns3/core-module.h"
#include"ns3/network-module.h"
#include"ns3/internet-module.h"
#include"ns3/application-module.h"

using namespace ns3;

int main(int argc,char *argv[]){
  NodeContainer nodes;
  nodes.Create(4);
  
  CsmaHelper csma;
  csma.SetDeviceAttribute("DataRate", StringValue ("5Mbps"));
  csma.SetChannelAttribute("Delay", StringValue ("2ms"));
  
  NetDeviceCollection devices;
  devices=csma.Install(nodes);
  
  InternetStackHelper stack;
  stack.Install(nodes);
  
  Ipv4AddreddHelper address;
  address.SetBase("10.1.1.0","255.255.255.0");
  
  Ipv4InterfaceContainer interfaces;
  interfaces=address.Assign(devices);
  
  UdpEchoServerHelper echoServer (9);
  
  ApplicationContainer serverApps= echoServer.Install(nodes.Get (1));
  serverApps.Start( Seconds (1.0));
  serverApps.Stop( Seconds (10.0));
  
  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute("MaxPackets",UintegerValue (1));
  echoClient.SetAttribute("Interval",TimeValue( Seconds (1.0)));
  echoClient.SetSttribute("PacketSize",UintegerValue (1024));
  
  ApplicationContainer clientApps= echoClient.Install(nodes.Get(0));
  clientApps.Start ( Seconds (2.0));
  clientApps.Stop ( Seconds (10.0));
  
  AnimationInterface anim ("second.xml");
  Simulator::Run ();
  Simulator::Destroy();
  return 0;
      
}

