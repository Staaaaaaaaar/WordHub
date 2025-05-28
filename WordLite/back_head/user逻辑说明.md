使用逻辑说明
首次启动应用：
自动创建 User 目录和数据库文件
创建默认 Guest 用户
用户需要调用createNewUser()注册新账户
已有用户：
自动加载用户数据
可以通过 setter 方法修改用户信息
可以通过verifyPassword()验证密码
重置用户：
调用resetUser(true)清除所有数据
恢复到 Guest 状态
需要重新注册
创建新用户：
只有 Guest 用户可以创建新用户
已登录用户需要先 reset