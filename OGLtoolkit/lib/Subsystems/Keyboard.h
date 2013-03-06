#ifndef KEYBOARD_H
#define KEYBOARD_H

/** Статический класс для обработки нажатых клавиш
  */
class Keyboard {
public:
        static bool     isKeyPressed(int key);
        static bool     isKeyReleased(int key);
};

#endif // KEYBOARD_H
