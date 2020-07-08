package scala.scalanative
package junit.plugin

// Ported from Scala.js

import scala.tools.nsc._

/** Hacks to have our source code compatible with all the versions of scalac
 *  that we support.
 *
 *  @author Nicolas Stucki
 */
trait CompatComponent {

  val global: Global

  import global._

  implicit final class DefinitionsCompat(
      self: CompatComponent.this.global.definitions.type) {

    def wrapVarargsArrayMethodName(elemtp: Type): TermName =
      self.wrapArrayMethodName(elemtp)

    def wrapArrayMethodName(elemtp: Type): TermName = infiniteLoop()
  }

  private def infiniteLoop(): Nothing =
    throw new AssertionError("Infinite loop in Compat210Component")
}
