from subprocess import call

def cat_doc():
    media = '/home/kaumi/my_software/python'
    media += '/Fiamma/doc.testo'
    call( 'cat "' + media + '"', shell = True )
    print()
    print()


def len_no_good( argv, numb, bigger = 0 ):
    if   bigger >  0 and len( argv ) >  numb: return True
    elif bigger == 0 and len( argv ) == numb: return True
    else:
        print( 'len argv no good, passed:', len( argv ) )
        exit()


def reader( fileX ):
    i = open( fileX, 'r' )
    for line in i.readlines(): yield line
    i.close()


def find_in_all_file( fileX, x, work, err ):
    cat = ''
    for line in reader( fileX ): cat += line
    if cat.count( x ):
        work += [ fileX ]
        return True
    else:
        err += [ fileX ]
        return False
