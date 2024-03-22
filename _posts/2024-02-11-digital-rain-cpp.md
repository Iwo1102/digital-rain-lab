---
layout: post
title: Summary
tags: cpp coding project
categories: demo
---

#Introduction
The way I decided to make this project was to have each line or *drop* be created by seperate objects with each in a seprate thread. This was so that there would be as little delay as possible when printing the lines.

#Desired Features:

Radomise character string:
rand and convert to ascii

Every 1 second a new line is created in a random position with a random length

The line does down 1 y position every 0.5 seconds with and once line length is reached it starts deleting top most characters
After y = 0 characters delete

object array where 1 object is a line and deletes itself once all characters are deleted

Change character colour with lowest being brightest

30% chance that the characters in the middle of the string change every 0.5 seconds

