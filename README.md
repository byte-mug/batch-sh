# batch-sh (under construction)
Non-Interactive Batch Shell for UNIX scripting

### Comparison

##### Example 1: if

###### Bourne shell
```
#!/bin/sh
if [ $days -gt 365 ]
then
   echo This is over a year.
fi
```

###### C shell
```
#!/bin/csh
if ( $days > 365 ) then
   echo This is over a year.
endif
```


###### Batch shell
```
#!/bin/???
if ( $days > 365 )
   echo This is over a year.
end
```

##### Example 2: while
Here is a second example, comparing scripts that calculate the first 10 powers of 2.

###### Bourne shell
```
#!/bin/sh
i=2
j=1
while [ $j -le 10 ]
do
   echo '2 **' $j = $i
   i=`expr $i '*' 2`
   j=`expr $j + 1`
done
```

###### C shell
```
#!/bin/csh
set i = 2
set j = 1
while ( $j <= 10 )
   echo '2 **' $j = $i
   @ i *= 2
   @ j++
end

```


###### Batch shell
```
#!/bin/???
$i = 2
$j = 1
while ( $j <= 10 )
   echo '2 **' $j '=' $i
   $i = $i * 2
   $j = $i + 1
end
```

