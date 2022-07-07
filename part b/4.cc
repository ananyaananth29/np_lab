#include"netanim-module.h"
#include"core-module.h"
#include"network-module.h"
#include"internet-module.h"
#include"point-to-point-module.h"
#include"applications-module.h"
#include"wifi-module.h"
#include"mobitlity-module.h"

using namespace ns3;

int main(int argc,char *argv[]){
  NodeContainer ptpnodes;
  ptpnodes.Ctreate (2);
  
  NodeContainer csmanodes;
  csmanodes.Add (ptpnodes.Get (1));
  csmanodes.Create (3);
  
  PointToPointHelper ptp;
  ptp.SetDeviceAttribute ("DataRate",StringValue ("5Mbps"));
  ptp.SetChannelAttribute ("Delay",StringValue ("2ms"));
  
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate",StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay",StringValue ("5ns"));
  csma.SetDeviceAttribute ("Mtu",UintegerValue (1400));
  
  NetDeviceContainer ptpdevices;
  ptpdevices=ptp.Intall (ptpnodes);
  
  NetDeviceContainer csmadevices;
  csmadevices=csma.Install (csmanodes));
  
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
  
  ApplicationContainer serverApps =echoServer.Install (csmanodes.Get (1), 9);
  serverApps.Start ( Seconds (1.0));
  serverApps.stop ( Seconds (10.0));
  
  UdpEchoClient echoClient (csmainterfaces.GetAddress (0));
  echoClient.SetAttribute ("MaxPackets",UintegerValue (1));
  echoClient.SetAttribute ("Interval",TimeValue ( Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize",UintegerValue (1024));
  
  ApplicationContainer clientApps =echoServer.Install (ptpnodes.Get (1), 9);
  clientApps.Start ( Seconds (2.0));
  clientApps.stop ( Seconds (10.0));
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  ptp.EnablePcapAll ("second");
  csma.EnablePcap ("second",csmadevices.Get (1), true);
  
  AnimationInterface anim ("anithird.xml");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
