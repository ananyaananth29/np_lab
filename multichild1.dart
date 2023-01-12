import 'package:flutter/material.dart';

void main() { runApp(MaterialApp( home: RowApp(), )); }
class RowApp extends StatelessWidget { // Our RowApp page inherits the traits of the Stateless Widget const RowApp({Key? key}) : super(key: key); @override Widget build(BuildContext context) { return body:Row( mainAxisAlignment: MainAxisAlignment.spaceEvenly, crossAxisAlignment: CrossAxisAlignment.start, children:[Container( height: 100, width: 100, color: Colors.blue, // change the color to red and green for other two containers child: Center( child: Text( 'First Child' ), ), ), ], ) // here we build the Widget Tree } }
