程式一說明:
	先輸入A(X)，先輸入係數，再輸入次方，並以次方遞減方式輸入
	如:3X^2+2x+4，就輸入3 2 2 1 4 0
	再輸入B(X)，以同樣格式，按ENTER後程式會自動跑出
	startA,finishA,startB,finishB,startD,finishD,avail的位置
	之後有個表格分別列出係數、次方、位置。

程式二說明:
	題目要求兩個array變一個，所以我就以array of structure把兩個array包起來變成一個。

程式三說明:
	不會打~~~~~~~

程式四說明:
	把sparse matrix 設為a_sparse[][]二維陣列,a_value[]一維陣列
	因為b可以自訂，我將b設為有10個值的 6x6 sparse matrix。
						|  98 |	
		| 0 0 0 1 1 1 | | -61 |
		| 1 0 1 0 1 0 | | -42 |
		| 0 0 0 0 1 1 | |  53 |
	b =	| 0 0 0 0 1 0 | |  84 |
		| 0 0 0 0 0 0 | | -12 |
		| 0 0 0 1 0 0 | | 142 | 
		   				|  35 |
		   				|  13 |
		   				| -53 |
	並與a相加，然後印出d sparse matrix。

程式五說明:
	先打一個strinins的副程式，讀入a,b兩個strings，再依照輸入的i把string a分開，放入string b
	全程沒有用到另一個temp string 。
