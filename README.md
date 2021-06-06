# AddressBook

Just an address book in terminal with ``CLI`` and ``TUI`` .  

🌎 English | [中文](README-CN.md)

## 💻Screenshot
![screenshot](https://link.jscdn.cn/1drv/aHR0cHM6Ly8xZHJ2Lm1zL3UvcyFBdDZScWFPaURhNk5rRnQ1QllMVzZmbUpuME8t.gif)

## ✨ Features

1. Generate contact information
2. Modify contact information
3. Delete contact information
4. Find contact information (by name, address and phone number)
5. Share contacts
6. Reset address book
7. Support ``CLI`` and ``TUI``
8. Design yourself theme
9. Add language pack

## ⚙️ How to designing yourself theme ?

1. You need create a file called ``theme.txt``.
2. Put it in to the AddressBook folder.
3. Then, you can strat to design yourself theme.  
   Here are some configurations:  

   **config tags for windows**
   - You have to write ``windowstag`` before you write windows tags configuration.
   - ``rightUpTag``, ``leftUpTag``, ``rightDownTag``, ``leftDownTag``, ``upAndDownTag``, ``leftAndRightTag``, ``tittleLeftTag`` and ``tittlrRightTag`` is to modify the tag configuration.
   - ``rightUpColor``, ``leftUpColor``, ``rightDownColor``, ``leftDownColor``, ``upAndDownColor``, ``leftAndRightColor``, ``tittleLeftColor`` and ``tittlrRightColor`` is to modify the tag color configuration.  

   **config information for windows**
   - You have to write ``windowsInfo`` before you write windows information configuration.  
   - ``logoElementX``, ``fliterElementX`` and ``indexElementX`` is to modify the element's position.
   - ``logoElementColor``, ``fliterElementColor``, ``indexElementColor``, ``guideElementColor``, ``foucerColor``, ``unforceColor``, and ``versionColor`` is to modify the element's color.  

**📝 e.g. >>> [theme.txt](theme.txt)**

```
windowsTag
    rightUpTag:╮
    rightDownTag:╯
    leftUpTag:╭
    leftDownTag:╰
    upAndDownTag:─
    leftAndRightTag:│
    titleLeftTag:<
    titleRightTag:>
    rightUpColor:(0,255,255)
    rightDownColor:(0,255,255)
    leftUpColor:(0,255,255)
    leftDownColor:(0,255,255)
    upAndDownColor:(0,255,255)
    leftAndRightColor:(0,255,255)
    titleLeftColor:(255,0,0)
    titleRightColor:(255,0,0)

windowsInfo
    logoElementX:3
    fliterElementX:17
    logoElementColor:(165,42,42)
    fliterElementColor:(165,42,42)
    indexElementColor:(0,255,255)
    fouceColor:(255,0,0)
    unfouceColor:(244,164,96)

```

## 🤝 Contribute
PR, Forks and any issue are welcome!