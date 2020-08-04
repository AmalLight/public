import libs

def cat2( fileX, da_cercare ):
    i = 1
    for line in libs.reader( fileX ):
         if line.count( da_cercare ): print( i, ':', line[:-1] )
         i += 1
