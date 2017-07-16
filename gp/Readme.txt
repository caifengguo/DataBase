外部数据装载
1 外部表的方式装载
如果数据在一个segment服务器上，则可以用 file：//协议 或者greenplum文件服务器gpfdist://协议
若数据需要从多个segment上来，则必须用greenplum文件服务器的方式
1，创建greenplum文件服务器
  1 从$GPHOME/bin 下面copy文件gpfdist到文件服务器上
  2 启动gpfdist :$gpfdist -d /var/load_files -p 8081 -l /home/gpadmin/log &
2，创建外部表
  create external table test_tom(name text,date date)
  location('gpfdist://etlhost:8081/*','gpfdist://etlhost1:8081/*')
  format 'text'(delimiter ',');
3，装载数据
  装载数据，用insert 或者create table *** as select * from from 外部表中

copy命令方式装载
copy命令装载数据并不是并行装载，而且所装载的数据文件必须放在master服务器上，例如：
copy country from‘/data/gpdb/country_data’ with delimiter '|' log errors into err_country segment reject limit 10 rows;