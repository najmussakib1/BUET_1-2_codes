import java.util.*

fun solve() {
    val sc = Scanner(System.`in`)
    if (!sc.hasNextInt()) return
    val t = sc.nextInt()
    repeat(t) {
        val k = sc.nextInt()
        
        var m = -1
        var n = -1
        var type = -1 // 0: internal, 1: one end, 2: two ends, 3: k=1 special
        
        if (k == 1) {
            n = 1
            type = 3
        } else if (k % 5 == 0) {
            m = k / 5
            n = 3 * m
            type = 0
        } else if (k % 5 == 3) {
            m = (k + 2) / 5
            n = 3 * m - 1
            type = 1
        } else if (k % 5 == 1) {
            m = (k + 4) / 5
            n = 3 * m - 2
            type = 2
        }
        
        if (n == -1) {
            println("NO")
        } else {
            println("YES")
            println(n)
            val grid = Array(2) { CharArray(n) { '.' } }
            
            when (type) {
                3 -> {
                    grid[0][0] = '*'
                }
                0 -> {
                    for (i in 0 until m) {
                        grid[0][3 * i + 1] = '*'
                    }
                }
                1 -> {
                    grid[0][0] = '*'
                    for (i in 1 until m) {
                        grid[0][3 * i] = '*'
                    }
                }
                2 -> {
                    for (i in 0 until m) {
                        grid[0][3 * i] = '*'
                    }
                }
            }
            
            println(grid[0].joinToString(""))
            println(grid[1].joinToString(""))
        }
    }
}

fun main() {
    solve()
}
