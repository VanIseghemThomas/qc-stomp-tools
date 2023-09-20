# Quad Cortex stomp tools

The idea for reverse engineering this, came from trying to run Doom on the Quad Cortex (which I actually succeeded in doing). The problem is that you can only watch the intro screen and do nothing. That brought me to the point of trying to reverse engineer how the stomps works.

In this repository you will find all kinds of utilities to interface with the stomps. In the `python` directory you will find my original scripts I used to reverse engineer the knobs, and some fun things I made to try and understand how to use them in fun ways. One of them is a control over websockets proof of concept!

The main part is the C-language implementation. This will allow you to compile a native executable for the Quad Cortex, and it will also be an important part of getting Doom to work.


## Stomp message byte examples:

**Action: button | Value: pressed**
```
9a e5 01 65 92 bf 0c 00 01 00 11 01 01 00 00 00 9a e5 01 65 92 bf 0c 00 00 00 00 00 00 00 00 00
```

**Action: button | Value: released**
```
9b e5 01 65 4b 74 0b 00 01 00 11 01 00 00 00 00 9b e5 01 65 4b 74 0b 00 00 00 00 00 00 00 00 00
```

**Action: rotary | Value: clock wise**
```
9d e5 01 65 ac 83 04 00 02 00 08 00 01 00 00 00 9d e5 01 65 ac 83 04 00 00 00 00 00 00 00 00 00
```

**Action: rotary | Value: counter clock**
```
9e e5 01 65 40 e8 05 00 02 00 08 00 ff 00 00 00 9e e5 01 65 40 e8 05 00 00 00 00 00 00 00 00 00
```

It seems that a 32 bytes message is divided into 2 parts of 16 bytes.

### Part 1 (first 16 bytes)
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10     | 11     | 12    | 13      | 14      | 15      |
|---|---|---|---|---|---|---|---|---|---|--------|--------|-------|---------|---------|---------|
| time | time | time | time | ? | ? | ? | padding? | action | action (not really used) | action | action | value | padding | padding | padding |

### Part 1 (last 16 bytes)
- 0 -> 6 are duplicates
- 7 -> 15 are padding

From first sight, this part look quite useless. Not sure why it's even there. Can maybe be used for cases where the listener is opened in the midst of receiving bytes. But the chance of that happening is super low, so this get's ignored for now.