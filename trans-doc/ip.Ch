IP(8) Linux IP(8)

名称
       IP - 显示/操作路由、网络设备、接口和隧道

简述
       ip [ OPTIONS ] OBJECT { COMMAND | help }

       ip [ -force ] -batch filename

       OBJECT := { link | address | addrlabel | route | rule | neigh | ntable | tunnel | tuntap | mad-
               | mroute | mrule | monitor | xfrm | netns | l2tp | tcp_metrics | token | macsec | vrf | mptc | ntp | ntable | tunnel | tuntap | mad-
               vrf | mptcp | ioam }

       OPTIONS := { -V[ersion] | -h[man-readable]|-s[tatistics]|-d[etails]|-r[esolve]|-iec||-f[amily] { in.
               -f[家庭] { inet | inet6 | link }| -4 | -6 | -B | -0 | -l[oops] { maximum-addr-flush-
               attempts }| -o[neline] | -rc[vbuf] [size] | -t[imestamp] | -ts[hort] | -n[etns] name | -N[umeric] | -t[imestamp] | -ts[hort] | -l[oops] { maximum-addr-flush- attempts }.
               -N[umeric] | -a[ll] | -c[olor] | -br[ief] | -j[son] | -p[retty] }

OPTIONS
       -V, -Version
              打印 ip 工具的版本并退出。

       -h, -human, -human-readable
              输出带后缀的人类可读值的统计数据。

       -b, -batch <FILENAME> (批处理)
              从提供的文件或标准输入中读取命令并调用它们。  第一次失败将
              将导致 ip 终止。

       -force 在批处理模式下，出错时不会终止 ip。  如果在执行
              命令时，应用程序返回代码将不为零。

       -s, -stats, -statistics
              输出更多信息。如果选项出现两次或两次以上，信息量就会增加。
              信息量就会增加。  通常情况下，信息是统计数据或一些时间值。

       -d、-details
              输出更详细的信息。

       -l, -loops <COUNT
              指定 "ip 地址刷新 "逻辑在放弃之前尝试的最大循环次数。
              最大循环次数。默认值为 10。  零 (0) 表示循环直至删除所有地址。

       -f, -family <FAMILY> （家族
              指定要使用的协议族。协议族标识符可以是 inet、
              inet6、bridge、mpls 或 link 中的一个。  如果不使用该选项，将从其他参数中猜测协议族。
              从其他参数中猜测。如果命令行的其余部分没有提供足够的信息
              信息，ip 就会返回默认值，通常是 inet 或 any。
              是一个特殊的族标识符，表示不涉及网络协议。

       -是 -family inet 的快捷方式。

       -6 -family inet6 的快捷方式。

       -B -family bridge 的快捷方式。

       -M -family mpls 的快捷方式。

       -0 -family link 的快捷方式。

       -o, -oneline
              单行输出每条记录，用"\"字符代替换行符。这在
              当你想用 wc(1) 或 grep(1) 来计算输出记录时，这很方便。

       -r、-resolve
              使用系统的名称解析器打印 DNS 名称而不是主机地址。

       -n、-netns <NETNS
              将 ip 切换到指定的网络名称空间 NETNS。  实际上，它只是简化了
              切：

              ip netns exec NETNS ip [ OPTIONS ] OBJECT { COMMAND | help }

              到

              ip -n[etns] NETNS [ OPTIONS ] OBJECT { COMMAND | help } 到

       -N,-数字
              直接打印协议、作用域、dsfield 等的编号，而不是将其转换为人类可读的名称。
              名称。

       -a、-all
              在所有对象上执行指定命令，取决于命令是否支持该选项。

       -c[color][={always|auto|never}（始终|自动|从不
              配置颜色输出。如果省略或始终省略参数，将启用颜色输出，而不考虑 stdout 状态。
              stdout状态。如果参数为 auto，则在启用彩色输出前会检查 stdout 是否为终端。
              颜色输出。如果参数为从不，则禁用彩色输出。如果多次指定
              多次，则最后一次优先。如果同时给出 -json，该标记将被忽略。

              使用的调色板受 COLORFGBG 环境变量影响（参见 ENVIRONMENT）。

       -t、-timestamp
              使用 monitor 选项时显示当前时间。

       -ts、-tshort
              与 -timestamp 类似，但使用更短的格式。

       -rc, -rcvbuf<SIZE>
              设置网连套接字接收缓冲区大小，默认为 1MB。

       -iec 以 IEC 单位打印人类可读的速率（例如 1Ki = 1024）。

       -br、-brief
              仅以表格格式打印基本信息，以提高可读性。该选项
              目前只有 ip addr show、ip link show 和 ip neigh show 命令支持该选项。

       -j, -json
              以 JavaScript Object Notation (JSON) 格式输出结果。

       -p, -pretty
              默认 JSON 格式紧凑，解析效率更高，但大多数用户很难
              读取。  此标记会增加缩进，以提高可读性。

ip - 命令语法
   对象
       地址
              - 设备上的协议（IP 或 IPv6）地址。

       添加标签
              - 标签配置，用于选择协议地址。

       ioam - 管理 IOAM 命名空间和 IOAM 模式。

       l2tp - IP 以太网隧道（L2TPv3）。

       link - 网络设备。

       maddress
              - 组播地址。

       监控
              - 监视网络链接信息。

       mptcp - 管理 MPTCP 路径管理器。

       mroute - 多播路由缓存条目。

       mrule - 多播路由选择策略数据库中的规则。

       邻居
              - 管理 ARP 或 NDISC 缓存项。

       netns - 管理网络命名空间。

       ntable - 管理邻居缓存的运行。

       route - 路由表条目。

       rule - 路由策略数据库中的规则。

       tcp_metrics/tcpmetrics
              - 管理 TCP 指标

       token - 管理标记化接口标识符。

       tunnel - IP 隧道。

       tuntap - 管理 TUN/TAP 设备。

       vrf - 管理虚拟路由和转发设备。

       xfrm - 管理 IPSec 策略。

       所有对象的名称都可以用全称或缩写形式书写，例如 address 可以缩写为 addr 或只是 a。
       缩写为 addr 或只是 a。

   命令
       指定要对对象执行的操作。  可能的操作集取决于对象类型。
       对象类型而定。  一般来说，可以添加、删除和显示（或列出）对象，但有些对象不允许执行所有这些操作，或者有一些附加命令。
       对象不允许执行所有这些操作，或者有一些附加命令。帮助命令
       可用于所有对象。它会打印出可用命令列表和参数语法说明。
       命令。

       如果没有给出命令，则默认为某个命令。  通常是 list，如果不能列出该类对象，则是 help。
       则为 help。

环境
       颜色
              如果设置，其值将用于检测背景是深色还是浅色，并为其使用同色系。
              对比色。

              COLORFGBG 环境变量通常包含两个或三个值，中间用分号隔开。
              无论哪种情况，我们都需要最后一个值。  如果该值为 0-6 或 8，则选择适合深色背景的颜色
              或适合深色背景的颜色：

              COLORFGBG=";0" ip -c a

退出状态
       如果命令成功，则退出状态为 0；如果出现语法错误，则退出状态为 1。  如果内核报错
       则退出状态为 2。

示例
       ip addr
           显示分配给所有网络接口的地址。

       ip neigh
           显示内核中的当前邻居表。

       ip link set x up
           调出 x 接口。

       ip link set x down
           关闭接口 x。

       ip 路由
           显示表路由。

历史
       ip 由 Alexey N. Kuznetsov 编写，在 Linux 2.2 中加入。

另请参见
       ip-address(8), ip-addrlabel(8), ip-ioam(8), ip-l2tp(8), ip-link(8), ip-maddress(8), ip-moni-
       tor(8), ip-mptcp(8), ip-mroute(8), ip-neighbour(8), ip-netns(8), ip-ntable(8), ip-route(8), ip-
       rule(8), ip-tcp_metrics(8), ip-token(8), ip-tunnel(8), ip-vrf(8), ip-xfrm(8)
       IP 命令参考 ip-cref.ps

报告错误
       请向 Network Developers 邮件列表 <netdev@vger.kernel.org> 报告任何错误。
       开发和维护工作主要在此进行。  您不必订阅该列表就可以向其发送信息。
       消息。

作者
       原始网页作者：Michail Litvak <mci@owl.openwall.com>

iproute2 2011 年 12 月 20 日 IP(8)
