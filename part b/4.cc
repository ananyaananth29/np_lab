#include"ns3/netanim-module.h"
#include"ns3/core-module.h"
#include"ns3/network-module.h"
#include"ns3/internet-module.h"
#include"ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include"ns3/applications-module.h"
#include"ns3/wifi-module.h"
#include "ns3/mobility-module.h"

using namespace ns3;

int main(int argc,char *argv[]){
  NodeContainer ptpnodes;
  ptpnodes.Create (2);
  
  NodeContainer csmanodes;
  csmanodes.Add (ptpnodes.Get (1));
  csmanodes.Create (3);
  
  PointToPointHelper ptp;
  ptp.SetDeviceAttribute ("DataRate",StringValue ("5Mbps"));
  ptp.SetChannelAttribute ("Delay",StringValue ("2ms"));
  
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate",StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay",StringValue ("6560ns"));
  
  NetDeviceContainer ptpdevices;
  ptpdevices=ptp.Install (ptpnodes);
  
  NetDeviceContainer csmadevices;
  csmadevices=csma.Install (csmanodes);
  
  InternetStackHelper stack;
  stack.Install (ptpnodes.Get (0));
  stack.Install (csmanodes);
  
  Ipv4AddressHelper ptpaddress;
  ptpaddress.SetBase ("10.1.1.0","255.255.255.0");
  
  Ipv4AddressHelper csmaaddress;
  csmaaddress.SetBase ("10.1.1.0","255.255.255.0");
  
  Ipv4InterfaceContainer ptpinterfaces;
  ptpinterfaces=ptpaddress.Assign (ptpdevices);
  
  Ipv4InterfaceContainer csmainterfaces;
  csmainterfaces=csmaaddress.Assign (csmadevices);
  
  UdpEchoServerHelper echoServer (9);
  
  ApplicationContainer serverApps =echoServer.Install (csmanodes.Get (3));
  serverApps.Start ( Seconds (1.0));
  serverApps.Stop ( Seconds (10.0));
  
  UdpEchoClientHelper echoClient (csmainterfaces.GetAddress (3), 9);
  echoClient.SetAttribute ("MaxPackets",UintegerValue (1));
  echoClient.SetAttribute ("Interval",TimeValue ( Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize",UintegerValue (1024));
  
  ApplicationContainer clientApps =echoServer.Install (ptpnodes.Get (0));
  clientApps.Start ( Seconds (2.0));
  clientApps.Stop ( Seconds (10.0));
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  ptp.EnablePcapAll ("second");
  csma.EnablePcap ("second",csmadevices.Get (1), true);
  
  AnimationInterface anim ("anithird.xml");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
