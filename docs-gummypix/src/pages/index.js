import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import HomepageFeatures from '@site/src/components/HomepageFeatures';

import Heading from '@theme/Heading';
import styles from './index.module.css';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <header className={clsx('hero hero--primary', styles.heroBanner)}>
      <div className="container">
        <Heading as="h1" className="hero__title">
          {siteConfig.title}
        </Heading>
        <p className="hero__subtitle">{siteConfig.tagline}</p>
        <div className={styles.buttons}>
          <Link
            className="button button--secondary button--lg"
            to="https://github.com/The-HaribOS-Organization/GummyPix">
            Download source code
          </Link>
        </div>
        <div className={styles.buttons}>
          <Link
            className="button button--secondary button--lg"
            to="docs/intro.md">
            View documentation
          </Link>
        </div>
      </div>
    </header>
  );
}

export default function Home() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <Layout
      title={`Hello from ${siteConfig.title}`}
      description="Description will go into a meta tag in <head />">
      <HomepageHeader />

      <main className="hero hero--primary">
        <div className="container">
          <h1 className="hero__title">Bienvenue dans GummiPix 🧸</h1>
            <p className="hero__subtitle">Librairie C graphique pour OS bas-niveau</p>
              <div className="buttons">
                <Link className="button button--secondary button--lg" to="/docs/intro">
                  Lire la documentation
                </Link>
              </div>
            </div>
          </main>
    </Layout>
  );
}
