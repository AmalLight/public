from libIO import dir_or_file
from cat2 import cat2
from sys import argv
import libs
import action

class Main:
        pre = None
        user = None
        home = None
        fiammaFiles = None
        err = None
        work = None
        argv = None
        outTree = None

        def __init__( self, argv, pre, user ):
                self.pre = pre
                self.user = user
                self.home = ( '/' + self.pre + '/' + self.user+'/' )
                self.err = []
                self.work = []
                self.argv = argv
                self.fiammaFiles = ( self.home + 'Fiamma_Files/' )
                self.outTree = ( self.fiammaFiles + 'Fiamma_tree' )
        
        def go(self):
                libs.cat_doc()
                if len( self.argv ) > 1:
                        b1 = self.argv[1] == 'find-line'
                        b2 = self.argv[1] == 'find-name'
                        b3 = self.argv[1] == 'cat2'
                        b4 = self.argv[1] == 'count'
                        b5 = self.argv[1] == 'delete'
                        b6 = self.argv[1] == 'tree'
                 
                        a = action.send( self.argv, self.work, self.err, self.pre, self.user )
        
                        if b1:
                                libs.len_no_good( self.argv, 3, 1 )
                            
                                # for any argv > 4 join to 4.
                                if len( self.argv ) > 5:
                                        resto = ( len( self.argv )-1 )
                                        while resto > 4:                                    
                                                self.argv[4] += ( ' ' + self.argv[ resto ] )
                                                self.argv=self.argv[ :resto ]
                                                resto -= 1
                        
                                libs.len_no_good( self.argv, 5, 0 )
                                dir_or_file( self.argv[2], a.find_line )
                                print()
                                print( '#WORK!!' )
                                print()
                                for el in self.work:
                                        print( el )
                                        cat2( el, self.argv[4] )
                                        print()
                                print()
                                print( '#WORK in:',    len( self.work ) )
                                print( '#NO WORK in:', len( self.err  ) )
                
                        elif b2 or b3 or b4 or b5: 
                                libs.len_no_good( self.argv, 4, 0 )
                               
                                if b2:
                                        dir_or_file( self.argv[2], a.find_name, a.find_name )
                                        print()
                                        print( '#WORK!!' )
                                        print()
                                        for el in self.work: print( el )
                                        print()
                                        print( '#WORK in:',    len( self.work ) )
                                        print( '#NO WORK in:', len( self.err  ) )
                                
                                elif b3:
                                        print()
                                        print( '#WORK!!' )
                                        print()
                                        print( self.argv[2] )
                                        cat2(  self.argv[2], self.argv[3] )
                                        print()
        
                                elif b4:
                                        if argv[3].count( 'all' ):
                                            if   argv[3] == 'all1': dir_or_file( self.argv[2], a.count_obj )
                                            elif argv[3] == 'all2': dir_or_file( self.argv[2], a.count_obj, a.count_obj )
                                        else: dir_or_file( self.argv[2], a.count_obj, a.count_obj )
                            
                                        print()
                                        print( '#WORK!!')
                                        print()
                                        print( '#COUNT is:',    len( self.work ) )
                                        print( '#NO COUNT is:', len( self.err  ) )
        
                                elif b5:
                                        if argv[3].count( 'all' ):
                                            if   argv[3] == 'all1': dir_or_file( self.argv[2], a.delete )
                                            elif argv[3] == 'all2': dir_or_file( self.argv[2], a.delete, a.delete )
                                        else: dir_or_file( self.argv[2], a.delete, a.delete )
                            
                                        print()
                                        print( '#WORK!!' )
                                        print()
                                        for el in self.work: print( el )
                                        print()
                                        print( '#DELETE in:',    len( self.work ) )
                                        print( '#NO DELETE in:', len( self.err  ) )
                        
                        elif b6:
                                libs.len_no_good( self.argv, 3, 0 )
                        
                                action.createX( self.outTree )
                                i = open( self.outTree, 'w' )
                                i.write( '\n   TREE OF:' + self.argv[2] + '\n\n' )
                                i.close()
                                dir_or_file( self.argv[2], a.tree, a.tree )
                                i = open( self.outTree, 'a' )
                                i.write( '\n   END OF TREE\n\n' )
                                i.close()
                                print()
                                print( '#WORK!!' )
                                print( '#OUT FILE in:', self.outTree )
                            
                input( "\n\t Press Enter key for finish. \n\n" )

start= Main(argv, 'home', 'kaumi')
start.go()
