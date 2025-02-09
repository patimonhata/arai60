# 141. Linked List Cycle 

進め方に迷って迷走しています。  
step 2 が複数あるなど。  
ご容赦ください...

~~leetcode 自体もこのコーディング練習も初めてだったので苦労しました。  
最初の accept までに1時間、 回答理解・納得まで30分くらい？  
その後コードレビューのための体制づくり(練習の進め方の理解、pull req を作る準備)に数時間。~~

---
## Step 0 : ~~最初に accept されたコード~~ 
このコードは accept されません。  
pointer でなく value を見ているので、cycle がなくとも重複した要素がある場合に true を返してしまいます。
数か月前のことで記憶が曖昧ですが、run だけしてコンパイルエラーがないので ok と思った?

```
C++

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::vector<int> val_already_used;
        int current_val;
        bool used;
        ListNode *current_ptr = head;

        while (current_ptr != NULL) {
            current_val = current_ptr->val;

            used = ( std::find(val_already_used.begin(), val_already_used.end(), current_val) != std::end(val_already_used) );
            if ( used == true) {
                return true;
            }

            val_already_used.push_back(current_val);
            current_ptr = current_ptr->next;
        }

        return false;

        
    }
};
```

#### 回答中の思考
- 問題文中の「内部的には pos が使われていて、末尾の次のポインタが接続されているノードのインデックスを指している」の意味を理解するのに時間を食った。
誤解して ListNode 構造体が引数として渡されるのではなく、{3, 2, 0, -4} のような配列が渡されるかと思ったりした。  
- まずは力づくで全探索するか。  
- vector 使ってる部分でメモリ効率は悪そう。  
- 今までに同じ要素が登場したか判定する際、メモリアドレス(ListNode へのポインタ)で比較する方法と要素そのもので比較する方法(回答の方法)どっちがいいんだ？  
  (最初はポインタの vector を用意してアドレスで比較していた。途中で要素で比較する方法に変えた。)
- std::vector::begin() や end() って空の vector の時どういう動作をするんだっけ？  
  → end() は要素の数に関係なく、「末尾の次の要素」を仮想的に表す定数 _past-the-end_ を返す。
    begin() は空の場合は定数 _past-the-end_ を返す。  
    よって、空の vector に対しても回答中の判定コードは期待通りの動作をする。
- 最初 `for (ListNode *current_ptr = head; current_ptr == null; current_ptr=current_ptr->next) {...}` で書いていたが、上手く動かず while にした。  
  for 文の内部処理の理解(停止条件の評価やイテレータ(?)の更新のタイミング)が甘いことに気付く。
- 現在のループで持っている値が過去に現れたかどうかを表す bool 変数の名前は used でいいのだろうか。
  少しひっかかる。より良い名前は思いつかない...
- constraints にある `The number of the nodes in the list is in the range [0, 10^4].`、`10^5 <= Node.val <= 10^5` という条件の味わい方が分からない。

#### 答えを見た後
- これは思いつかないなあ
- なぜこれで上手く判定できるんだ？証明したいな  
  → できた  
    (定数 c が任意に与えられた時、サイクルの長さを m として c+2n = n (mod m) となる n がいつでも存在するかという問題に帰着される。)
- 確かにO(1)のメモリしか使っていなくてすごい
- (空の配列を引数として受け取った時の処理を書いているのを見て) 特別な処理は必要？メインの処理で対応可能だった場合に、明示的に分けて書いた方が親切？


---

## Step 1

https://1kohei1.com/leetcode/ から解答の動画を見て、フロイドのうさぎとかめについて知った。  


```
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow_ptr = head;
        ListNode *fast_ptr = head;
        
        if (head == NULL) return false; 
        //論理の「ならば」と同様に考えるのならば true とするのが望ましい？

        while (fast_ptr != NULL) {
            if (fast_ptr->next == NULL) break;

            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
            
            if (fast_ptr == slow_ptr) return true; //if there is a cycle
        }
        
        return false;
    }
};
```

- 入力が空の配列の時、true と false のどちらを返すのが望ましい？  
論理で考えると、true ? (「AならばB」 は 「not A または B」なので)  
このコードがどのように使われるかがあまり想像できていないので悩む。  
true が返ってきたときに無意識に「入力が空でない、かつ、サイクルがある」と思われそうなのが懸念。

## Step 2-1


直近同じ問題を解いた人のコードを見た。  
https://github.com/quinn-sasha/leetcode/pull/1  
https://github.com/Fuminiton/LeetCode/pull/1  

プルリクエストの見方がよく分からない。(ファイルの中身全部を見れているのか変更だけ見れているのか...)


修正後のコード
```
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow_ptr = head;   // slow pointer moves 1 node forward at a time
        ListNode *fast_ptr = head;   // fast pointer moves 2 node forward at a time
        
        if (head == NULL) return true; 

        while (fast_ptr != NULL) {
            if (fast_ptr->next == NULL) return false;   // when reached the end of a linked list

            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
            
            if (fast_ptr == slow_ptr) return true;   // found the cycle
        }
    }
};
```
- 入力が空だったときは true を返すようにしました。
- コメントを付けました。

- ごちゃごちゃしていて読みにくいという認識はあるが、直し方がよく分からない。

- フロイドのうさぎとかめについて  
  常識に入っているわけではないらしい。  
  このアルゴリズムの発見経緯(?)、認知度を調べようとは思わなかった。
  「解答の動画が採用しているのだから、これは常識に含まれており最適な解法のはずだ」という思い込みがあった。
  
## Step 2-2
set を使って解くことにした。  
set を使ったことないので調べるところから。


  


