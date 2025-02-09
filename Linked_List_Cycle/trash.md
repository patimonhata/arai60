# このファイルは数か月前に初めて練習を始めようとしたときの記録です。
# 念のため残しますが見る必要はありません。

















# 141. Linked List Cycle を解きました。  

leetcode 自体もこのコーディング練習も初めてだったので苦労しました。  
最初の accept までに1時間、 回答理解・納得まで30分くらい？  
その後コードレビューのための体制づくり(練習の進め方の理解、pull req を作る準備)に数時間。

---
## Step 1 : 最初に accept されたコード 
回答を書いている最中や答えを見た際に考えたことをコードの後に書きます。

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

## Step 2 : 
