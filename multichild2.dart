import "package:flutter/material.dart";
void main() {
runApp(MaterialApp(
debugShowCheckedModeBanner: false,
home:SafeArea(
child:ColumnApp(),
),
));
}
class ColumnApp extends StatefulWidget {
const ColumnApp({Key? key}) : super(key: key);
@override
_ColumnAppState createState() =>; _ColumnAppState();
}
class _ColumnAppState extends State<ColumnApp> {
@override
Widget build(BuildContext context) {
return Scaffold(
body:Row(
mainAxisAlignment: MainAxisAlignment.spaceBetween,
children:[
Column(
mainAxisAlignment: MainAxisAlignment.start,
children:[Container(
height: 100,
width: 100,
color: Colors.red,
child: Center(
child: Text(
"First Child",
),
),
),
],
),
Column(
mainAxisAlignment: MainAxisAlignment.center,
children: [Container(
height: 100,
width: 100,
color: Colors.blue,
child: Center(
child: Text(
"Second Child",
),
),
),
],
),
Column(
mainAxisAlignment: MainAxisAlignment.end,
children:[Container(
height: 100,
width: 100,
color: Colors.green,
child: Center(
child: Text(
"Third Child",
),
),
),
],
),
],
),
);
}}
