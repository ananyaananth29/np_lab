//flutter:
//  uses-material-design: true
//  assets:
//    - images/

import 'package:flutter/material.dart';
import 'dart:math';
void main() { runApp(MaterialApp( home:Scaffold( appBar: AppBar(title: Text('DICEE'),centerTitle: true,), // Simple Appbar body: DicePage(), // body now points to a DicePage which is a stateful widget ), )); } class DicePage extends StatefulWidget { const DicePage({Key? key}) : super(key: key); @override _DicePageState createState() => _DicePageState(); }
class _DicePageState extends State<DicePage> {int left = 1 ; // set the first image number to left int right = 2 ; // set the second image number to right void changeface(){ setState(() {left = Random().nextInt(6)+1; // Random() belongs to Math library right = Random().nextInt(6)+1 ; // Random().nextInt(6)- generates random number between 1-6, excluding 6. // to include 6 as well, add 1 to it. }); } @override @override Widget build(BuildContext context) { return Center( child: Container( child: Row( children: [ Expanded( flex: 1, child: TextButton( style: TextButton.styleFrom( backgroundColor: Colors.blueAccent, ), child:Image.asset('images/dice$left.png'), // dynamically changes the image number onPressed: (){ changeface(); // calls the UI change on button pressed }, ), ), Expanded( flex: 1, child: TextButton( style: TextButton.styleFrom( backgroundColor: Colors.blueAccent, ), child:Image.asset('images/dice$right.png'), // dynamically changes the image number onPressed: (){ changeface(); // calls the UI change on button pressed }, ), ), ], ), ), ); } }
