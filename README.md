# AddressBook

用于记录联系方式的小工具，支持CLI。

## 实现功能

1. 添加联系方式
2. 修改联系方式
3. 删除联系方式
4. 查找联系方式（姓名查找，地址查找，号码查找）
5. 分享联系人卡片
6. 重置通讯录
7. 支持CLI 操作方式

## CLI

1. 添加联系方式  
   longOptName: ``add``  
   shortOptName: ``-a``  
   command:  
   ``./AddressBook add <name>``  
   or  
   ``./AddressBook -a <name>``  

2. 修改联系方式  
   longOptName: ``change``  
   shortOptName: ``-chg``  
   command:  
   ``./AddressBook change <name> <element> <value>``  
   or  
   ``./AddressBook -chg <name> <element> <value>``  

3. 删除联系方式  
   longOptName: ``remove``  
   shortOptName: ``-mv``  
   command: ``./AddressBook remove <name>`` or ``./AddressBook -mv <name>``  

4. 查找联系方式  
   longOptName: ``find``  
   shortOptName: ``-f``  
   command:  
   ``./AddressBook find <by element> <value>``  
   or  
   ``./AddressBook -f <by element> value``  

5. 分享联系人卡片  
   longOptName：``share``  
   shortOptName: ``-s``  
   command:  
   ``./AddressBook share <name>``  
   or  
   ``./AddressBook -s <name>``  

6. 查看通讯录  
   longOptName: ``view``  
   shortOptName: ``-v``  
   command:  
   ``./AddressBook view``  
   or  
   ``./AddressBook -v``  

7. 重置通讯录  
   longOptName: ``reset``  
   command: ``./AddressBook reset``  

8. 查看命令行操作  
   longOptName: ``help``  
   shortOptName: ``-h``
   command:  
   ``./AddressBook help <option>``  
   or  
   ``./AddressBook -h <optList>``
