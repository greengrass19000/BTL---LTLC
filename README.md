*Bài tập lớn môn lập trình nâng cao 
  Name : Nguyễn Bá Nam Dũng
  MSV : 20020040 

*GAME : PACMAN
*

*Tài liệu tham khảo :

    Nguồn của code liên quan đến SDL : https://lazyfoo.net/tutorials/SDL/ (các code ở đây em chỉ đọc hiểu rồi paste trực tiếp vào code của mình)

    Image resource : http://labs.phaser.io/assets/games/pacman/ 

    Sound resource : https://www.sounds-resource.com/arcade/pacman/sound/10603/

*Mô tả trò chơi:
 
Cách chơi giống với trò Pacman kinh điển, người chơi sẽ phải di chuyển nhân vật ăn hết các điểm trên ô để hoàn thành 3 màn chơi, với độ khó tăng dần :
  
    Màn 1 : Dễ nhất
    
    Màn 2 : Tăng bán kính tìm thấy Pacman của 4 quái vật (sử dụng BFS từ Pacman để tìm đường đi ngắn nhất từ các con quái đến nó
    
    Màn 3 : Tăng độ khó bằng việc hạn chế tầm nhìn của nhân vật
    
    *Một số cách khác để tăng điểm : - nuốt các quái vật khi chúng hoảng sợ
                                     - ăn thêm trái cây xuất hiện trên bản đồ
    
    
P/S : Do thiếu kinh nghiệm về cả SDL kết hợp một thời gian dài không code nên các source của game em đều hardcode @@ 
