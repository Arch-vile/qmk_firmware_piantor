# Sherwood Split - easy navigation

"Sherwood Split" is a name that takes inspiration from the legendary English folk hero, Robin Hood, who was known for his exceptional skills as an archer and his uncanny ability to split an arrow with another. The name "Sherwood Split" represents the design of the keyboard layout, where the navigation keys are distinctively separated on either side, replicating the act of splitting an arrow.

To be done still:
[ ] Change page ups and home to be gui + arrow instead. it is usable in more scenarios. in intellij cmd + arrow up is nice feature. But then how to go beginning of file? with vim commands yes. but in other programs. Is page up still needed in addition
[X] How to do gui + number. need to add modifiers to numbers layer. how to make the modifiers constant on all layers on thumb cluster? It can be done by activating the mod on base layer first.
[X] also backspace would be nice on symbols layer.
[X] Change the app instance change to use pinky button, feels more comfortable
[X] double shift for capsword not working as it is a shortcut on intellij. need to come up with something else. just do extra tap after.

needed new features 
- CAPSWORD - activated by both shifts pressed
- Take use of the repeat button

Features
- Base layer MODs can be activated and than applied to keys on other layers

Main principles:
- Writing code does not require moving thumb
- Minimize pinky usage
    - Favor the use of other fingers over pinky
    - Home row pinky okish
- Favor two sided layout for maximum home row finger usage
- homerow mods did not work for me for the often fast typed things
    - shifted letters
    - symbols
    - But we for sure can use homerow mods on layers for things that do not need to be activated in typing frenzy
- Keep QWERTY
    - To not make it overly hard to adapt
- Think from scratch
    - No need to place keys in any way to mimic normal full size keyboard positions
- Only use two thumb keys for layers, as thumb get’s confused with many layers
    - Abandon the  principle of single half layers only, let’s use both halfs of the layers
    - Accessing layers
        - Left thumb1: layer1
        - Left thumb2: layer2
        - Right thumb1: layer 3
        - Right thumb2: layer 4
        - Left thumb1 + right thumb1: layer 5
        - Left thumb2 + right thumb2: layer 6

Changes:
- Numpad does not seem to work for me
- try out double tap on symbols layer, DID NOT WORK. problems with TAP TERM delays being same for hold mods and double taps. sluggish,
- change to vimnavigation or actually variation of it?
    - have the navigation on one row instead of normal arrow formation on multiple lines
    - having the “arrows” on one line makes it possible to fit three navigation alternatives nicely on same half. One navigation per line. could that work?
    - But we need shift it so that it is on jkl; instead of hjkl because first of all it does not make any sense why it is hjkl; instead of the homerow buttons. and most importantly because doing mouse movement one needs to press at the same time multiple directions and going bottom left ⬇️⬅️ would be extremely cumbersome with hjkl
        - NO! We should split the up and down to make it super easy to have mouse movement. Easy to press to directions at the same time.
    - for example text editing:
        - middle row: normal arrow functionality
        - top row
            - left/right: move by word
            - up/down: start/end of line
        - bottom row:
            - left/right: ?
            - up/down: start/end of document
        - or app navigation, tab navigation, pane navigation.

how to incorporate the idea of different level of app management
- desktop
- app
- tabs
- panes

For future
- Could the symbol layer be one shot activation? With this we could activate two layers from same thumb. one with tap other with hold.
- Use double tap on base layer to bring missing common keys
    - double `..` for `?`
    - double `,,` for !
    -

Shortcomings
- QMK does not allow having shifted key codes e.g. KC_LPRN inside tap mods SFT_T(KC_LPRN) it will just send the unsifted symbol, 9 here
