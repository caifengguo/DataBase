�ⲿ����װ��
1 �ⲿ��ķ�ʽװ��
���������һ��segment�������ϣ�������� file��//Э�� ����greenplum�ļ�������gpfdist://Э��
��������Ҫ�Ӷ��segment�������������greenplum�ļ��������ķ�ʽ
1������greenplum�ļ�������
  1 ��$GPHOME/bin ����copy�ļ�gpfdist���ļ���������
  2 ����gpfdist :$gpfdist -d /var/load_files -p 8081 -l /home/gpadmin/log &
2�������ⲿ��
  create external table test_tom(name text,date date)
  location('gpfdist://etlhost:8081/*','gpfdist://etlhost1:8081/*')
  format 'text'(delimiter ',');
3��װ������
  װ�����ݣ���insert ����create table *** as select * from from �ⲿ����

copy���ʽװ��
copy����װ�����ݲ����ǲ���װ�أ�������װ�ص������ļ��������master�������ϣ����磺
copy country from��/data/gpdb/country_data�� with delimiter '|' log errors into err_country segment reject limit 10 rows;